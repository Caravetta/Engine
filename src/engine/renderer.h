#if !defined(RENDERER_H)

#include <vector>
#include "../core/core.h"


typedef enum {
    SET_PROJ_MATRIX,
    SET_VIEW_MATRIX,
    BIND_SHADER,
    UNBIND_SHADER,
    BIND_MESH,
    RENDER_MESH,
    UNBIND_MESH,
    DRAW_ELEMENTS,
} command_type_t;

struct render_command_t {
    command_type_t command_type;
    unsigned int shader_id;
    core::Handle mesh_handle;
    union {
        core::Matrix4f projection_matrix;
        core::Matrix4f view_matrix;
        core::Matrix4f transformation_matrix;
    };
    render_command_t(){}
};

typedef struct {
    unsigned int shader_id;
    core::Matrix4f projection_matrix;
    core::Matrix4f view_matrix;
    Mesh_Asset* mesh_asset;
    int projection_matrix_id;
    int view_matrix_id;
    int transformation_matrix_id;
} render_state_t;

std::vector<render_command_t> render_command_queue;

std::vector<render_command_t> internal_command_queue;

void generate_commands()
{
    // This will parse the render_command_queue and generate the internal_command_queue
    struct mesh_info_t {
        core::Handle mesh_handle;
        std::vector<core::Matrix4f> mesh_transforms;
    };

    struct shader_split {
        unsigned int shader_id;
        uint64_t mesh_idx;
        std::unordered_map<uint64_t, uint64_t> mesh_map;
        std::vector<struct mesh_info_t> mesh_vector;
    };

    std::unordered_map<unsigned int, uint64_t> shader_map;
    std::vector<struct shader_split> split_vector(20); //TODO: fix this resize should not be static
    uint64_t split_index = 0;

    core::Matrix4f projection_matrix;
    core::Matrix4f view_matrix;

    for (int i = 0; i < render_command_queue.size(); i++) {

        switch(render_command_queue[i].command_type) {
        case SET_PROJ_MATRIX: {
            projection_matrix = render_command_queue[i].projection_matrix;
        } break;
        case SET_VIEW_MATRIX: {
            view_matrix = render_command_queue[i].view_matrix;
        } break;
        case RENDER_MESH: {
            uint64_t shader_index = 0;
            // look to see if we have seen this shader
            std::unordered_map<unsigned int, uint64_t>::const_iterator shader_map_ele = shader_map.find(render_command_queue[i].shader_id);
            if ( shader_map_ele != shader_map.end() ) {
                shader_index = shader_map_ele->second;
            } else {
                // we have not seen it before
                split_vector[split_index].shader_id = render_command_queue[i].shader_id;
                split_vector[split_index].mesh_vector.resize(30); //TODO: fix this resize should not be static
                split_vector[split_index].mesh_idx = 0;
                shader_map.insert({ render_command_queue[i].shader_id, split_index});
                shader_index = split_index;
                split_index++;
            }

            //look to see if we have seen this mesh before
            std::unordered_map<uint64_t, uint64_t>::const_iterator mesh_ele = split_vector[shader_index].mesh_map.find(render_command_queue[i].mesh_handle);
            if ( mesh_ele != split_vector[shader_index].mesh_map.end() ) {
                split_vector[shader_index].mesh_vector[mesh_ele->second].mesh_transforms.push_back(render_command_queue[i].transformation_matrix);
            } else {
                // we have not seen this mesh
                split_vector[shader_index].mesh_map.insert({ render_command_queue[i].mesh_handle, split_vector[shader_index].mesh_idx});
                split_vector[shader_index].mesh_vector[split_vector[shader_index].mesh_idx].mesh_transforms.push_back(render_command_queue[i].transformation_matrix);
                split_vector[shader_index].mesh_idx++;
            }

        } break;
        default: {

        } break;
        }
    }

    uint64_t total_command_size = 0;

    total_command_size += 2;

    total_command_size += split_index * 2;

    for ( int i = 0; i < split_index; i++ ) {
        total_command_size += split_vector[i].mesh_idx * 2;
        for ( int j = 0; j < split_vector[i].mesh_idx; j++ ) {
            total_command_size += split_vector[i].mesh_vector[j].mesh_transforms.size();
        }
    }

    render_command_queue.clear();

    internal_command_queue.resize(total_command_size);

    // generate the internal commands
    uint64_t cmd_idx = 0;

    internal_command_queue[cmd_idx].command_type = SET_PROJ_MATRIX;
    internal_command_queue[cmd_idx].projection_matrix = projection_matrix;
    cmd_idx++;

    internal_command_queue[cmd_idx].command_type = SET_VIEW_MATRIX;
    internal_command_queue[cmd_idx].view_matrix = view_matrix;
    cmd_idx++;

    for ( int i = 0; i < split_index; i++ ) {
        internal_command_queue[cmd_idx].command_type = BIND_SHADER;
        internal_command_queue[cmd_idx].shader_id = split_vector[i].shader_id;
        cmd_idx++;

        for ( int j = 0; j < split_vector[i].mesh_idx; j++ ) {
            internal_command_queue[cmd_idx].command_type = BIND_MESH;
            internal_command_queue[cmd_idx].mesh_handle = split_vector[i].mesh_vector[j].mesh_handle;
            cmd_idx++;

            for ( int k = 0; k < split_vector[i].mesh_vector[j].mesh_transforms.size(); k++ ) {
                internal_command_queue[cmd_idx].command_type = DRAW_ELEMENTS;
                internal_command_queue[cmd_idx].transformation_matrix = split_vector[i].mesh_vector[j].mesh_transforms[k];
                cmd_idx++;
            }

            internal_command_queue[cmd_idx].command_type = UNBIND_MESH;
            cmd_idx++;
        }

        internal_command_queue[cmd_idx].command_type = UNBIND_SHADER;
        cmd_idx++;
    }

}

void render()
{
    generate_commands();

    render_state_t render_state;

    for (int i = 0; i < internal_command_queue.size(); i++) {

        switch( internal_command_queue[i].command_type ) {
        case SET_PROJ_MATRIX: {
            render_state.projection_matrix = internal_command_queue[i].projection_matrix;
        } break;
        case SET_VIEW_MATRIX: {
            render_state.view_matrix = internal_command_queue[i].view_matrix;
        } break;
        case BIND_SHADER: {
            glUseProgram(internal_command_queue[i].shader_id);
            render_state.projection_matrix_id = glGetUniformLocation(internal_command_queue[i].shader_id, "projection_matrix");
            render_state.view_matrix_id = glGetUniformLocation(internal_command_queue[i].shader_id, "view_matrix");
            render_state.transformation_matrix_id = glGetUniformLocation(internal_command_queue[i].shader_id, "transformationMatrix");
            glUniformMatrix4fv(render_state.projection_matrix_id, 1, GL_FALSE, (GLfloat *)&render_state.projection_matrix);
            glUniformMatrix4fv(render_state.view_matrix_id, 1, GL_FALSE, (GLfloat *)&render_state.view_matrix);
        } break;
        case UNBIND_SHADER: {
            glUseProgram(0);
        } break;
        case BIND_MESH: {
            Engine::get_instance()->asset_manager->get_asset<Mesh_Asset>(internal_command_queue[i].mesh_handle, &render_state.mesh_asset);
            render_state.mesh_asset->mesh.vao->bind();
            render_state.mesh_asset->mesh.vao->bind_attributes();
        } break;
        case UNBIND_MESH: {
            render_state.mesh_asset->mesh.vao->unbind_attributes();
            render_state.mesh_asset->mesh.vao->unbind();
        } break;
        case DRAW_ELEMENTS: {
            glUniformMatrix4fv(render_state.transformation_matrix_id, 1, GL_FALSE, (GLfloat *)&internal_command_queue[i].transformation_matrix);
            glDrawElements(GL_TRIANGLES, render_state.mesh_asset->mesh.indices_count, GL_UNSIGNED_INT, 0);
        } break;
        default: {
            LOG_ERROR("Unknown render command");
        } break;
        };
    }
}


#define RENDERER_H
#endif
