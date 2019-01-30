#include <unordered_map>
#include "renderer.h"
#include "thread.h"
#include "math_utils.h"
#include "mesh_manager.h"
#include "material_manager.h"
#include "texture_manager.h"

namespace Engine {

std::vector<render_command_t> render_command_queue;
std::vector<opengl_command_t> internal_command_queue;
uint64_t internal_command_count;

lock_t render_command_queue_lock;

void enqueue_render_command( render_command_t command )
{
    render_command_queue.push_back(command);
}

void lock_render_queue()
{

}

void release_render_queue()
{

}

typedef struct {
    std::vector<uint32_t> material_idx;
    uint32_t shader_id;
} shader_info_list_t;

typedef struct {
    std::vector<Matrix4f> transformation_matrix_vec;
    uint64_t enabled_state;
} mesh_group_info_t;

typedef struct {
    vao_t* vao;
    uint32_t indices_count;
    std::unordered_map<uint64_t, uint32_t> enable_state_map;
    std::vector<mesh_group_info_t> mesh_group_vec;
} mesh_entry_t;

typedef struct {
    Material* material;
    std::unordered_map<uint64_t, uint32_t> mesh_handle_map;
    std::vector<mesh_entry_t> mesh_entry_vec;
} material_entry_t;

void _generate_commands(std::vector<opengl_command_t>* opengl_commands, Camera* camera)
{
    uint64_t enabled_state = 0;

    std::vector<material_entry_t> material_entry_vec;
    std::unordered_map<uint64_t, uint32_t> material_handle_map; // key = material handle id | value = material_entry_vec index

    std::vector<shader_info_list_t> shader_info_list;
    std::unordered_map<uint32_t, uint32_t> shader_id_map;

    /*
     * We first need to loop through all commands to sort them.
     * Sort Order:
     *  - Shader
     *  - Texture
     *  - Mesh / vao
     */

     /*
      * build uint64_t key from shader + texture uint32_t for both
      *
      */
	for (uint64_t i = 0; i < render_command_queue.size(); i++) {

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

            uint32_t material_vec_idx;

            std::unordered_map<uint64_t, uint32_t>::const_iterator ele = material_handle_map.find(render_command_queue[i].material_handle.id);
            if ( ele == material_handle_map.end() ) {
                // we have not seen this material

                material_entry_t material_entry;
                material_entry.material = Material_Manager::get_material(render_command_queue[i].material_handle);
                material_entry_vec.push_back(material_entry);

                material_handle_map.insert({ render_command_queue[i].material_handle.id, (uint32_t)material_entry_vec.size() - 1 });

                material_vec_idx = (uint32_t)material_entry_vec.size() - 1;
            } else {
                material_vec_idx = ele->second;
            }

            uint32_t shader_vec_idx;

            std::unordered_map<uint32_t, uint32_t>::const_iterator shader_ele = shader_id_map.find(material_entry_vec[material_vec_idx].material->shader_id);
            if ( shader_ele == shader_id_map.end() ) {
                shader_info_list_t shader_info;
                shader_info.shader_id = material_entry_vec[material_vec_idx].material->shader_id;
                shader_info_list.push_back(shader_info);
                shader_id_map.insert({ material_entry_vec[material_vec_idx].material->shader_id, (uint32_t)shader_info_list.size() - 1 });
                shader_vec_idx = (uint32_t)shader_info_list.size() - 1;
            } else {
                shader_vec_idx = shader_ele->second;
            }

            shader_info_list[shader_vec_idx].material_idx.push_back(material_vec_idx);

            uint32_t mesh_vec_idx;

            // check to see if we have seen this mesh along with this material
            ele = material_entry_vec[material_vec_idx].mesh_handle_map.find(render_command_queue[i].mesh_handle.id);
            if ( ele == material_entry_vec[material_vec_idx].mesh_handle_map.end() ) {
                // we have not seen this mesh yet

                mesh_entry_t mesh_entry;
                mesh_entry.vao = Mesh_Manager::get_mesh_vao(render_command_queue[i].mesh_handle);
                mesh_entry.indices_count = Mesh_Manager::get_indices_count(render_command_queue[i].mesh_handle);

                material_entry_vec[material_vec_idx].mesh_entry_vec.push_back(mesh_entry);

                material_entry_vec[material_vec_idx].mesh_handle_map.insert({ render_command_queue[i].mesh_handle.id, (uint32_t)material_entry_vec[material_vec_idx].mesh_entry_vec.size() - 1});
                mesh_vec_idx = (uint32_t)material_entry_vec[material_vec_idx].mesh_entry_vec.size() - 1;
            } else {
                mesh_vec_idx = ele->second;
            }

            uint32_t enable_idx;

            ele = material_entry_vec[material_vec_idx].mesh_entry_vec[mesh_vec_idx].enable_state_map.find(enabled_state);
            if ( ele == material_entry_vec[material_vec_idx].mesh_entry_vec[mesh_vec_idx].enable_state_map.end() ) {
                mesh_group_info_t mesh_group;
                mesh_group.enabled_state = enabled_state;
                material_entry_vec[material_vec_idx].mesh_entry_vec[mesh_vec_idx].mesh_group_vec.push_back(mesh_group);

                material_entry_vec[material_vec_idx].mesh_entry_vec[mesh_vec_idx].enable_state_map.insert({ enabled_state, (uint32_t)material_entry_vec[material_vec_idx].mesh_entry_vec[mesh_vec_idx].mesh_group_vec.size() - 1 });
                enable_idx = (uint32_t)material_entry_vec[material_vec_idx].mesh_entry_vec[mesh_vec_idx].mesh_group_vec.size() - 1;
            } else {
                enable_idx = ele->second;
            }

            material_entry_vec[material_vec_idx].mesh_entry_vec[mesh_vec_idx].mesh_group_vec[enable_idx].transformation_matrix_vec.push_back(render_command_queue[i].transformation_matrix);

        } break;
        case RESERVED: {
            LOG("RESERVED");
        } break;
        default: {
            LOG_ERROR("Uknown render_command " << render_command_queue[i].command_type);
        } break;
        };
    }

    uint64_t current_enable_state = 0;
    int transform_uniform_id = -1;

    for ( uint32_t ii = 0; ii < shader_info_list.size(); ++ii ) {
        // change shader here
        {
            opengl_command_t new_command;
            new_command.command_type = BIND_SHADER;
            new_command.shader_id = shader_info_list[ii].shader_id;
            opengl_commands->push_back(new_command);
        }
        {
            opengl_command_t new_command;
            new_command.command_type = UNIFORM_MAT4;
            new_command.uniform_info.matrix4f = camera->projection_matrix;
            new_command.uniform_info.id = glGetUniformLocation(shader_info_list[ii].shader_id, "projection_matrix");

            if ( new_command.uniform_info.id == -1 ) {
                LOG_ERROR("projection_matrix is not a uniform in shader id " << shader_info_list[ii].shader_id);
            } else {
                opengl_commands->push_back(new_command);
            }
        }
        {
            opengl_command_t new_command;
            new_command.command_type = UNIFORM_MAT4;
            new_command.uniform_info.matrix4f = camera->view_matrix;
            new_command.uniform_info.id = glGetUniformLocation(shader_info_list[ii].shader_id, "view_matrix");

            if ( new_command.uniform_info.id == -1 ) {
                LOG_ERROR("view_matrix is not a uniform in shader id " << shader_info_list[ii].shader_id);
            } else {
                opengl_commands->push_back(new_command);
            }
        }

        transform_uniform_id = glGetUniformLocation(shader_info_list[ii].shader_id, "transformationMatrix");

        for ( uint32_t jj = 0; jj < shader_info_list[ii].material_idx.size(); ++jj ) {

            uint32_t material_index = shader_info_list[ii].material_idx[jj];

            Material* current_material = material_entry_vec[material_index].material;

            uint32_t current_texture_unit = 0;
            for ( uint32_t tt = 0; tt < current_material->element_info_vec.size(); ++tt ) {
                switch( current_material->element_info_vec[tt].type ) {
                case VEC3_ELEMENT: {
                    opengl_command_t new_command;
                    new_command.command_type = UNIFORM_VEC3;
                    new_command.uniform_info.vector3f = *current_material->get_element<Vector3f>(current_material->element_info_vec[tt].element_name);
                    new_command.uniform_info.id = glGetUniformLocation(shader_info_list[ii].shader_id, current_material->element_info_vec[tt].element_name.c_str());

                    if ( new_command.uniform_info.id == -1 ) {
                        LOG_ERROR(current_material->element_info_vec[tt].element_name << " is not a uniform in shader id " << shader_info_list[ii].shader_id);
                    } else {
                        opengl_commands->push_back(new_command);
                    }
                } break;
                case MATRIX4_ELEMENT: {
                    opengl_command_t new_command;
                    new_command.command_type = UNIFORM_MAT4;
                    new_command.uniform_info.matrix4f = *current_material->get_element<Matrix4f>(current_material->element_info_vec[tt].element_name);
                    new_command.uniform_info.id = glGetUniformLocation(shader_info_list[ii].shader_id, current_material->element_info_vec[tt].element_name.c_str());

                    if ( new_command.uniform_info.id == -1 ) {
                        LOG_ERROR(current_material->element_info_vec[tt].element_name << " is not a uniform in shader id " << shader_info_list[ii].shader_id);
                    } else {
                        opengl_commands->push_back(new_command);
                    }
                } break;
                case TEXT_HANDLE_ELEMENT: {
                    opengl_command_t new_command;
                    new_command.command_type = UNIFORM_TEXT;
                    Texture_Handle texture_handle = *current_material->get_element<Texture_Handle>(current_material->element_info_vec[tt].element_name);
                    new_command.uniform_info.texture_id = Texture_Manager::get_texture_id(texture_handle);
                    new_command.uniform_info.id = glGetUniformLocation(shader_info_list[ii].shader_id, current_material->element_info_vec[tt].element_name.c_str());
                    new_command.uniform_info.texture_unit = current_texture_unit++;

                    if ( new_command.uniform_info.id == -1 ) {
                        LOG_ERROR(current_material->element_info_vec[tt].element_name << " is not a uniform in shader id " << shader_info_list[ii].shader_id);
                    } else {
                        opengl_commands->push_back(new_command);
                    }
                } break;
                default: {
                    LOG_ERROR("Unsupported data type");
                } break;
                }
            }

            for ( uint32_t kk = 0; kk < material_entry_vec[material_index].mesh_entry_vec.size(); ++kk ) {

                // bind the vao here
                {
                    opengl_command_t new_command;
                    new_command.command_type = BIND_VAO;
                    new_command.vao_info.vao = material_entry_vec[material_index].mesh_entry_vec[kk].vao;
                    opengl_commands->push_back(new_command);
                }

                for ( uint32_t ll = 0; ll < material_entry_vec[material_index].mesh_entry_vec[kk].mesh_group_vec.size(); ++ll ) {
                    if ( material_entry_vec[material_index].mesh_entry_vec[kk].mesh_group_vec[ll].enabled_state != current_enable_state ) {
                        current_enable_state = material_entry_vec[material_index].mesh_entry_vec[kk].mesh_group_vec[ll].enabled_state;

                        if ( (current_enable_state & BLEND_ENABLED) > 0 ) {
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

                        if ( (current_enable_state & DEPTH_TEST_ENABLED) > 0 ) {
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

                        if ( (current_enable_state & CULL_FACE_ENABLED) > 0 ) {
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
                    }

                    for ( uint32_t pp = 0; pp < material_entry_vec[material_index].mesh_entry_vec[kk].mesh_group_vec[ll].transformation_matrix_vec.size(); ++pp ) {
                        //set mesh transform here
                        {
                            opengl_command_t new_command;
                            new_command.command_type = UNIFORM_MAT4;
                            new_command.uniform_info.id = transform_uniform_id;
                            new_command.uniform_info.matrix4f = material_entry_vec[material_index].mesh_entry_vec[kk].mesh_group_vec[ll].transformation_matrix_vec[pp];

                            if ( new_command.uniform_info.id == -1 ) {
                                LOG_ERROR( "transformationMatrix is not a uniform in shader id " << shader_info_list[ii].shader_id );
                            } else {
                                opengl_commands->push_back(new_command);
                            }
                        }
                        // add a draw command
                        {
                            opengl_command_t new_command;
                            new_command.command_type = DRAW_ELEMENTS;
                            new_command.draw_data.indices_count = material_entry_vec[material_index].mesh_entry_vec[kk].indices_count;
                            opengl_commands->push_back(new_command);
                        }
                    }
                }
            }
        }
    }
}

void render( Camera* camera, int width, int height )
{
    //START_TIME_BLOCK(render);
    glEnable( GL_MULTISAMPLE );
    glViewport(0, 0, width, height);
    glClearColor(0.16f, 0.29f, 0.48f, 0.54f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    std::vector<opengl_command_t> opengl_commands;
    _generate_commands(&opengl_commands, camera);

	for (uint64_t i = 0; i < opengl_commands.size(); i++) {
        switch( opengl_commands[i].command_type ) {
        case BIND_SHADER: {
            glUseProgram(opengl_commands[i].shader_id);
            #if 0
            projection_matrix_id = glGetUniformLocation(opengl_commands[i].shader_id, "projection_matrix");
            view_matrix_id = glGetUniformLocation(opengl_commands[i].shader_id, "view_matrix");
            transformation_matrix_id = glGetUniformLocation(opengl_commands[i].shader_id, "transformationMatrix");
            color_id = glGetUniformLocation(opengl_commands[i].shader_id, "color");

            if ( projection_matrix_id != -1 ) {
                 glUniformMatrix4fv(projection_matrix_id, 1, GL_FALSE, (GLfloat *)&camera->projection_matrix);
            }
            if ( view_matrix_id != -1 ) {
                 glUniformMatrix4fv(view_matrix_id, 1, GL_FALSE, (GLfloat *)&camera->view_matrix);
            }
            #endif
        } break;
        case UNBIND_SHADER: {
            glUseProgram(0);
        } break;
        case BIND_VAO: {
            bind_vao(opengl_commands[i].vao_info.vao);
            bind_vao_attributes(opengl_commands[i].vao_info.vao);
        } break;
        case UNBIND_VAO: {
            unbind_vao_attributes(opengl_commands[i].vao_info.vao);
            unbind_vao();
        } break;
        case DRAW_ELEMENTS: {
            //glUniformMatrix4fv(transformation_matrix_id, 1, GL_FALSE, (GLfloat *)&opengl_commands[i].draw_data.transformation_matrix);
            //glUniform3fv(color_id, 1, (GLfloat *)&color);
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
        case UNIFORM_VEC3: {
            glUniform3fv(opengl_commands[i].uniform_info.id, 1, (GLfloat *)&opengl_commands[i].uniform_info.vector3f);
        } break;
        case UNIFORM_MAT4: {
            glUniformMatrix4fv(opengl_commands[i].uniform_info.id, 1, GL_FALSE, (GLfloat *)&opengl_commands[i].uniform_info.matrix4f);
        } break;
        case UNIFORM_TEXT: {
            glUniform1i(opengl_commands[i].uniform_info.id, opengl_commands[i].uniform_info.texture_unit);

            glActiveTexture(GL_TEXTURE0 + opengl_commands[i].uniform_info.texture_unit);

            glBindTexture(GL_TEXTURE_2D, opengl_commands[i].uniform_info.texture_id);
        } break;
        default: {
            LOG_ERROR("Unknown OpenGL command " << opengl_commands[i].command_type);
        }
        }
    }

    render_command_queue.erase(render_command_queue.begin(), render_command_queue.begin() + render_command_queue.size());
    //END_TIME_BLOCK(render);
}

} // end namespace Engine
