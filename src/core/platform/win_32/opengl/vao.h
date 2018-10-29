#ifndef __VAO_H__
#define __VAO_H__

#include "vbo.h"
#include "opengl.h"

namespace core {

typedef enum {
    STATIC_DRAW = GL_STATIC_DRAW,
    DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
} usage_type_t;

typedef struct {
    std::vector<vbo_t>              vbos;
    std::unordered_map<int, size_t> attribute_map;
    unsigned int                    id;
    vbo_t                           indices_vbo;
} vao_t;

CORE_API void create_vao( vao_t* vao );
CORE_API void bind_vao( vao_t* vao );
CORE_API void unbind_vao();
CORE_API void bind_vao_attributes( vao_t* vao );
CORE_API void unbind_vao_attributes( vao_t* vao );
CORE_API void create_index_buffer( vao_t* vao, int* indices, int num_indices, usage_type_t usage_type );
CORE_API void create_float_attribute( vao_t* vao, int attribute, float* data, int data_size, int attribute_size, usage_type_t usage_type );
CORE_API void create_int_attribute( vao_t* vao, int attribute, int* data, int data_size, int attribute_size, usage_type_t usage_type );
CORE_API void update_index_buffer( vao_t* vao, int* indices, int num_indices, usage_type_t usage_type );
CORE_API void update_float_attribute( vao_t* vao, int attribute, float* data, int data_size, usage_type_t usage_type );
CORE_API void update_int_attribute( vao_t* vao, int attribute, int* data, int data_size, usage_type_t usage_type );

} //end namespace core

#endif //__VAO_H__
