#if !defined(RENDERER_H)

#include <vector>
#include "../core/core.h"

//glBindTexture(GL_TEXTURE_2D, font_asset->font.tex);

//TODO: add checks in to make sure ids do not go higher then the max uint32_t
#define TEXTURE_MASK 0xFFFFFFFF
#define SHADER_TEXTURE_KEY( shader_id, texture_id ) (uint64_t)texture_id << 32 | (uint64_t)shader_id
#define GET_SHADER_ID( shader_texture_key ) ( shader_texture_key >> 32 )
#define GET_TEXTURE_ID( shader_texture_key ) ( shader_texture_key & TEXTURE_MASK )

typedef enum {
    RESERVED,
    RENDER_MESH,
    RENDER_TEXT,
    SET_PROJ_MATRIX,
    SET_VIEW_MATRIX,
    SET_ORTHO_MATRIX,
    ENABLE_BLEND,
    DISABLE_BLEND,
    ENABLE_DEPTH_TEST,
    DISABLE_DEPTH_TEST,
    ENABLE_CULL_FACE,
    DISABLE_CULL_FACE,
    ENABLE_VSYNC,
    DISABLE_VSYNC,
} render_command_type_t;

typedef enum {
    GL_ENABLE,
    GL_DISABLE,
    BIND_SHADER,
    UNBIND_SHADER,
    BIND_VAO,
    UNBIND_VAO,
    DRAW_ELEMENTS,
    BIND_TEXTURE,
    UNBIND_TEXTURE,
} opengl_command_type_t;

typedef enum {
    VSYNC_ENABLED       = 1 << 0,
    CULL_FACE_ENABLED   = 1 << 1,
    DEPTH_TEST_ENABLED  = 1 << 2,
    BLEND_ENABLED       = 1 << 3,
} opengl_settings_type_t;

typedef enum {
    BLEND_TYPE,
    DEPTH_TEST_TYPE,
    CULL_FACE_TYPE,
} opengl_type;

typedef enum {
    VAO_2D,
    VAO_3D,
} vao_D_type_t;

struct render_command_t {
    render_command_type_t   command_type;
    unsigned int            shader_id;
    core::vao_t*            vao;
    uint32_t                indices_count;
    unsigned int            texture_id;
    core::Vector3f          position;
    union {
        core::Matrix4f projection_matrix;
        core::Matrix4f view_matrix;
        core::Matrix4f transformation_matrix;
        core::Matrix4f ortho_projection_matrix;
    };
    render_command_t(){}
};

struct opengl_command_t {
    opengl_command_type_t command_type;
    union {
        opengl_type type;
        uint32_t shader_id;
        struct {
            core::vao_t*   vao;
        } vao_info;
        uint32_t texture_id;
        core::Matrix4f projection_matrix;
        core::Matrix4f view_matrix;
        struct {
            core::Matrix4f transformation_matrix;
            uint32_t       indices_count;
            vao_D_type_t   d_type;
            core::Vector3f position;
        } draw_data;
        core::Matrix4f ortho_projection_matrix;
    };
    opengl_command_t(){}
};

typedef struct {
    uint32_t shader_id;
    core::Matrix4f projection_matrix;
    core::Matrix4f view_matrix;
    Mesh_Asset* mesh_asset;
    int projection_matrix_id;
    int view_matrix_id;
    int transformation_matrix_id;
} render_state_t;

#ifdef WINDOWS_PLATFORM
CRITICAL_SECTION render_command_queue_lock;
#endif

void lock_render_queue()
{
#ifdef WINDOWS_PLATFORM
    EnterCriticalSection(&render_command_queue_lock);
#endif
}

void release_render_queue()
{
#ifdef WINDOWS_PLATFORM
    LeaveCriticalSection(&render_command_queue_lock);
#endif
}

std::vector<render_command_t> render_command_queue;

std::vector<opengl_command_t> internal_command_queue;
uint64_t internal_command_count;

// sorted data stored in below structs

typedef struct {
    core::vao_t* vao;
    vao_D_type_t d_type;
    uint32_t   indices_count;
    std::vector<core::Matrix4f> vao_pos;
    std::vector<core::Vector3f> vao_pos_3f;
} vao_info_t;

typedef struct {
    uint32_t texture_id;
    std::unordered_map<uint64_t, uint64_t> vao_map;
    std::vector<vao_info_t> vao_info;
} texture_info_t;

typedef struct {
    uint32_t shader_id;
    std::unordered_map<uint64_t, uint64_t> texture_map;
    std::vector<texture_info_t> texture_info;
} shader_info_t;

typedef struct {
    uint64_t enable_state;
    std::unordered_map<uint64_t, uint64_t> shader_map;
    std::vector<shader_info_t> shader_info;
} enabled_state_info_t;

void generate_commands(std::vector<opengl_command_t>* opengl_commands)
{
    //LOG("generate_commands() start");
    uint64_t enabled_state = 0;

    std::vector<enabled_state_info_t> enable_state_info;
    std::unordered_map<uint64_t, uint64_t> enabled_state_map;  //<enabled_state, enable_state_info idx>

    /*
     * We first need to loop through all commands to sort them.
     * Sort Order:
     *  - Enable state
     *  - Shader
     *  - Texture
     *  - Mesh / vao
     */

     /*
      * build uint64_t key from shader + texture uint32_t for both
      *
      */
    for (int i = 0; i < render_command_queue.size(); i++) {

        switch(render_command_queue[i].command_type) {
        case ENABLE_BLEND: {
            enabled_state |= BLEND_ENABLED;
        } break;
        case DISABLE_BLEND: {
            enabled_state &= ~BLEND_ENABLED;
        } break;
        case ENABLE_DEPTH_TEST: {
            enabled_state |= DEPTH_TEST_ENABLED;
        } break;
        case DISABLE_DEPTH_TEST: {
            enabled_state &= ~DEPTH_TEST_ENABLED;
        } break;
        case ENABLE_CULL_FACE: {
            enabled_state |= CULL_FACE_ENABLED;
        } break;
        case DISABLE_CULL_FACE: {
            enabled_state &= ~CULL_FACE_ENABLED;
        } break;
        case SET_ORTHO_MATRIX: {

        } break;
        case SET_VIEW_MATRIX: {

        } break;
        case SET_PROJ_MATRIX: {

        } break;
        case RENDER_TEXT:
        case RENDER_MESH: {
            /*
             * Steps
             * - get map for enable_state
             * - get map for shader/texture key
             * - see if mesh has been seen if not add mesh if has been seen add new position to position array for mesh
             */
            uint64_t shader_texture_key = SHADER_TEXTURE_KEY(render_command_queue[i].texture_id, render_command_queue[i].shader_id);
            enabled_state_info_t* enabled_statep = NULL;
            shader_info_t* shader_infop = NULL;
            texture_info_t* texture_infop = NULL;
            vao_info_t* vao_infop = NULL;

            std::unordered_map<uint64_t, uint64_t>::const_iterator ele = enabled_state_map.find(enabled_state);
            if ( ele != enabled_state_map.end() ) {
                 enabled_statep = &enable_state_info[ele->second];
            } else {
                 enabled_state_info_t temp_enable_state;
                 enable_state_info.push_back(temp_enable_state);
                 enabled_state_map.insert({ enabled_state, enable_state_info.size() - 1 });
                 enabled_statep = &enable_state_info[enable_state_info.size() - 1];
                 enabled_statep->enable_state = enabled_state;
            }

            ele = enabled_statep->shader_map.find(render_command_queue[i].shader_id);
            if ( ele != enabled_statep->shader_map.end() ) {
                 shader_infop = &enabled_statep->shader_info[ele->second];
            } else {
                 shader_info_t temp_shader;
                 enabled_statep->shader_info.push_back(temp_shader);
                 enabled_statep->shader_map.insert({ render_command_queue[i].shader_id, enabled_statep->shader_info.size() - 1 });
                 shader_infop = &enabled_statep->shader_info[enabled_statep->shader_info.size() - 1];
                 shader_infop->shader_id = render_command_queue[i].shader_id;
            }

            ele = shader_infop->texture_map.find(render_command_queue[i].texture_id);
            if ( ele != shader_infop->texture_map.end() ) {
                 texture_infop = &shader_infop->texture_info[ele->second];
            } else {
                 texture_info_t temp_texture;
                 shader_infop->texture_info.push_back(temp_texture);
                 shader_infop->texture_map.insert({ render_command_queue[i].texture_id, shader_infop->texture_info.size() - 1 });
                 texture_infop = &shader_infop->texture_info[shader_infop->texture_info.size() - 1];
                 texture_infop->texture_id = render_command_queue[i].texture_id;
            }

            uint64_t vao_id = render_command_queue[i].vao->id;
            ele = texture_infop->vao_map.find(vao_id);
            if (  ele != texture_infop->vao_map.end() ) {
                  vao_infop = &texture_infop->vao_info[ele->second];
            } else {
                  vao_info_t temp_vao;
                  texture_infop->vao_info.push_back(temp_vao);
                  texture_infop->vao_map.insert({ vao_id, texture_infop->vao_info.size() - 1 });
                  vao_infop = &texture_infop->vao_info[texture_infop->vao_info.size() - 1];
                  vao_infop->vao = render_command_queue[i].vao;
                  vao_infop->indices_count = render_command_queue[i].indices_count;
                  if ( render_command_queue[i].command_type == RENDER_MESH ) {
                       vao_infop->d_type = VAO_3D;
                  } else {
                       vao_infop->d_type = VAO_2D;
                  }
            }

            if ( render_command_queue[i].command_type == RENDER_MESH ) {
                 vao_infop->vao_pos.push_back(render_command_queue[i].transformation_matrix);
            } else {
                 vao_infop->vao_pos_3f.push_back(render_command_queue[i].position);
            }

        } break;
        case RESERVED: {
            LOG("RESERVED");
        } break;
        default: {
            LOG_ERROR("Uknown render_command " << render_command_queue[i].command_type);
        } break;
        };
    }

    for (int i = 0; i < enable_state_info.size(); i++) {
        if ( (enable_state_info[i].enable_state & BLEND_ENABLED) > 0 ) {
             opengl_command_t new_command;
             new_command.command_type = GL_ENABLE;
             new_command.type = BLEND_TYPE;
             opengl_commands->push_back(new_command);
        } else {
             opengl_command_t new_command;
             new_command.command_type = GL_DISABLE;
             new_command.type = BLEND_TYPE;
             opengl_commands->push_back(new_command);
        }

        if ( (enable_state_info[i].enable_state & DEPTH_TEST_ENABLED) > 0 ) {
             opengl_command_t new_command;
             new_command.command_type = GL_ENABLE;
             new_command.type = DEPTH_TEST_TYPE;
             opengl_commands->push_back(new_command);
        } else {
             opengl_command_t new_command;
             new_command.command_type = GL_DISABLE;
             new_command.type = DEPTH_TEST_TYPE;
             opengl_commands->push_back(new_command);
        }

        if ( (enable_state_info[i].enable_state & CULL_FACE_ENABLED) > 0 ) {
             opengl_command_t new_command;
             new_command.command_type = GL_ENABLE;
             new_command.type = CULL_FACE_TYPE;
             opengl_commands->push_back(new_command);
        } else {
             opengl_command_t new_command;
             new_command.command_type = GL_DISABLE;
             new_command.type = CULL_FACE_TYPE;
             opengl_commands->push_back(new_command);
        }

        std::vector<shader_info_t>* shader_info_vecp = &enable_state_info[i].shader_info;

        for (int j = 0; j < shader_info_vecp->size(); j++) {
            opengl_command_t bind_shader_command;
            bind_shader_command.command_type = BIND_SHADER;
            bind_shader_command.shader_id = shader_info_vecp->at(j).shader_id;
            opengl_commands->push_back(bind_shader_command);

            std::vector<texture_info_t>* texture_info_vecp = &shader_info_vecp->at(j).texture_info;
            for (int k = 0; k < texture_info_vecp->size(); k++) {
                opengl_command_t bind_texture_command;
                bind_texture_command.command_type = BIND_TEXTURE;
                bind_texture_command.texture_id = texture_info_vecp->at(k).texture_id;
                opengl_commands->push_back(bind_texture_command);

                std::vector<vao_info_t>* vao_info_vecp = &texture_info_vecp->at(k).vao_info;

                for (int m = 0; m < vao_info_vecp->size(); m++) {
                    opengl_command_t bind_vao_command;
                    bind_vao_command.command_type = BIND_VAO;
                    bind_vao_command.vao_info.vao = vao_info_vecp->at(m).vao;
                    opengl_commands->push_back(bind_vao_command);

                    if (vao_info_vecp->at(m).d_type == VAO_3D) {
                    for (int l = 0; l < vao_info_vecp->at(m).vao_pos.size(); l++) {
                        opengl_command_t draw_vao_command;
                        draw_vao_command.command_type = DRAW_ELEMENTS;
                        draw_vao_command.draw_data.indices_count = vao_info_vecp->at(m).indices_count;
                        if ( vao_info_vecp->at(m).d_type == VAO_3D ) {
                             draw_vao_command.draw_data.d_type = VAO_3D;
                             draw_vao_command.draw_data.transformation_matrix = vao_info_vecp->at(m).vao_pos[l];
                        } else {
                             draw_vao_command.draw_data.d_type = VAO_2D;
                             draw_vao_command.draw_data.position = vao_info_vecp->at(m).vao_pos_3f[l];
                        }
                        opengl_commands->push_back(draw_vao_command);
                    }
                    } else {
                    for (int l = 0; l < vao_info_vecp->at(m).vao_pos_3f.size(); l++) {
                        opengl_command_t draw_vao_command;
                        draw_vao_command.command_type = DRAW_ELEMENTS;
                        draw_vao_command.draw_data.indices_count = vao_info_vecp->at(m).indices_count;
                             draw_vao_command.draw_data.d_type = VAO_2D;
                             draw_vao_command.draw_data.position = vao_info_vecp->at(m).vao_pos_3f[l];
                        opengl_commands->push_back(draw_vao_command);
                    }

                    }

                    opengl_command_t unbind_vao_command;
                    unbind_vao_command.command_type = UNBIND_VAO;
                    unbind_vao_command.vao_info.vao = vao_info_vecp->at(m).vao;
                    opengl_commands->push_back(unbind_vao_command);
                }

                opengl_command_t unbind_texture_command;
                unbind_texture_command.command_type = UNBIND_TEXTURE;
                unbind_texture_command.texture_id = 0;
                opengl_commands->push_back(unbind_texture_command);
            }

            opengl_command_t unbind_shader_command;
            unbind_shader_command.command_type = UNBIND_SHADER;
            unbind_shader_command.shader_id = 0;
            opengl_commands->push_back(unbind_shader_command);
        }

    }

}
#define GL_MULTISAMPLE                    0x809D
void render()
{
    START_TIME_BLOCK(render);
    glEnable( GL_MULTISAMPLE );
    glViewport(0, 0, Engine::get_instance()->window->get_width(), Engine::get_instance()->window->get_height());
    glClearColor(0.16f, 0.29f, 0.48f, 0.54f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

#if 1
    std::vector<opengl_command_t> opengl_commands;
    generate_commands(&opengl_commands);

    int projection_matrix_id = -1;
    int view_matrix_id = -1;
    int transformation_matrix_id = -1;
    int ortho_matrix_id = -1;
    int pos_id = -1;

    for (int i = 0; i < opengl_commands.size(); i++) {
        switch( opengl_commands[i].command_type ) {
        case BIND_SHADER: {
            glUseProgram(opengl_commands[i].shader_id);
            projection_matrix_id = glGetUniformLocation(opengl_commands[i].shader_id, "projection_matrix");
            view_matrix_id = glGetUniformLocation(opengl_commands[i].shader_id, "view_matrix");
            transformation_matrix_id = glGetUniformLocation(opengl_commands[i].shader_id, "transformationMatrix");
            ortho_matrix_id = glGetUniformLocation(opengl_commands[i].shader_id, "ortho_matrix");
            pos_id = glGetUniformLocation(opengl_commands[i].shader_id, "pos");

            if ( projection_matrix_id != -1 ) {
                 glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, (GLfloat *)&Engine::get_instance()->debug_camera->projection_matrix);
            }
            if ( view_matrix_id != -1 ) {
                 glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, (GLfloat *)&Engine::get_instance()->debug_camera->view_matrix);
            }
            if ( ortho_matrix_id != -1 ) {
                 glUniformMatrix4fv(ortho_matrix_id, 1, GL_FALSE, (GLfloat *)&Engine::get_instance()->debug_camera->ortho_matrix);
            }
        } break;
        case UNBIND_SHADER: {
            glUseProgram(0);
        } break;
        case BIND_VAO: {
            core::bind_vao(opengl_commands[i].vao_info.vao);
            core::bind_vao_attributes(opengl_commands[i].vao_info.vao);
        } break;
        case UNBIND_VAO: {
            core::unbind_vao_attributes(opengl_commands[i].vao_info.vao);
            core::unbind_vao();
        } break;
        case DRAW_ELEMENTS: {
            if ( (transformation_matrix_id != -1) && (opengl_commands[i].draw_data.d_type == VAO_3D) ) {
                 glUniformMatrix4fv(transformation_matrix_id, 1, GL_FALSE, (GLfloat *)&opengl_commands[i].draw_data.transformation_matrix);
            } else if ( (pos_id != -1) && (opengl_commands[i].draw_data.d_type == VAO_2D) ) {
                 glUniform2f(pos_id, opengl_commands[i].draw_data.position.vec.x, opengl_commands[i].draw_data.position.vec.y);
            }
            glDrawElements(GL_TRIANGLES, opengl_commands[i].draw_data.indices_count, GL_UNSIGNED_INT, 0);
        } break;
        case BIND_TEXTURE: {
            glBindTexture(GL_TEXTURE_2D, opengl_commands[i].texture_id);
        } break;
        case UNBIND_TEXTURE: {
            glBindTexture(GL_TEXTURE_2D, 0);
        } break;
        case GL_ENABLE: {
            switch( opengl_commands[i].type ) {
            case BLEND_TYPE: {
                glEnable(GL_BLEND);
            } break;
            case DEPTH_TEST_TYPE: {
                glEnable(GL_DEPTH_TEST);
                glDepthFunc(GL_LESS);
            } break;
            case CULL_FACE_TYPE: {
                glEnable(GL_CULL_FACE);
            } break;
            default: {
                LOG_ERROR("Unknown OpenGL enable type " << opengl_commands[i].type);
            }
            }
        } break;
        case GL_DISABLE: {
            switch( opengl_commands[i].type ) {
            case BLEND_TYPE: {
                glDisable(GL_BLEND);
            } break;
            case DEPTH_TEST_TYPE: {
                glDisable(GL_DEPTH_TEST);
            } break;
            case CULL_FACE_TYPE: {
                glDisable(GL_CULL_FACE);
            } break;
            default: {
                LOG_ERROR("Unknown OpenGL disable type " << opengl_commands[i].type);
            }
            }
        } break;
        default: {
            LOG_ERROR("Unknown OpenGL command " << opengl_commands[i].command_type);
        }
        }
    }
#endif
    render_command_queue.erase(render_command_queue.begin(), render_command_queue.begin() + render_command_queue.size());
    END_TIME_BLOCK(render);
}


#define RENDERER_H
#endif
