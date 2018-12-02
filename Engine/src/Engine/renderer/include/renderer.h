#if !defined(RENDERER_H)

#include <vector>
#include "core_common.h"
#include "vao.h"
#include "platform.h"
#include "Engine.h"

//glBindTexture(GL_TEXTURE_2D, font_asset->font.tex);

namespace Engine {

//TODO: add checks in to make sure ids do not go higher then the max uint32_t
#define TEXTURE_MASK 0xFFFFFFFF
#define SHADER_TEXTURE_KEY( shader_id, texture_id ) (uint64_t)texture_id << 32 | (uint64_t)shader_id
#define GET_SHADER_ID( shader_texture_key ) ( shader_texture_key >> 32 )
#define GET_TEXTURE_ID( shader_texture_key ) ( shader_texture_key & TEXTURE_MASK )
#define GL_MULTISAMPLE                    0x809D //move to platform layer

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
    vao_t*            vao;
    uint32_t                indices_count;
    unsigned int            texture_id;
    Vector3f          position;
    union {
        Matrix4f projection_matrix;
        Matrix4f view_matrix;
        Matrix4f transformation_matrix;
        Matrix4f ortho_projection_matrix;
    };
    render_command_t(){}
};

struct opengl_command_t {
    opengl_command_type_t command_type;
    union {
        opengl_type type;
        uint32_t shader_id;
        struct {
            vao_t*   vao;
        } vao_info;
        uint32_t texture_id;
        Matrix4f projection_matrix;
        Matrix4f view_matrix;
        struct {
            Matrix4f transformation_matrix;
            uint32_t       indices_count;
            vao_D_type_t   d_type;
            Vector3f position;
        } draw_data;
        Matrix4f ortho_projection_matrix;
    };
    opengl_command_t(){}
};

typedef struct {
    uint32_t shader_id;
    Matrix4f projection_matrix;
    Matrix4f view_matrix;
    //Mesh_Asset* mesh_asset;
    int projection_matrix_id;
    int view_matrix_id;
    int transformation_matrix_id;
} render_state_t;

typedef struct {
    vao_t* vao;
    vao_D_type_t d_type;
    uint32_t   indices_count;
    std::vector<Matrix4f> vao_pos;
    std::vector<Vector3f> vao_pos_3f;
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

void lock_render_queue();
void release_render_queue();
void enqueue_render_command( render_command_t command );
void render( Camera* camera, int width, int height );

} // end namespace Engine

#define RENDERER_H
#endif
