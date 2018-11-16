#include "vao.h"
#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>

namespace core {

void create_vao( vao_t* vao )
{
    glGenVertexArrays(1, &vao->id);
}

void bind_vao( vao_t* vao )
{
    glBindVertexArray(vao->id);
}

void unbind_vao()
{
    glBindVertexArray(0);
}

void bind_vao_attributes( vao_t* vao )
{
    //TODO(JOSH): need to fix how this is done
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void unbind_vao_attributes( vao_t* vao )
{
    //TODO(JOSH): need to fix how this is done
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);

}

void create_index_buffer( vao_t* vao, int* indices, int num_indices, usage_type_t usage_type )
{
    vao->indices_vbo.type = GL_ELEMENT_ARRAY_BUFFER;
    allocate_vbo(&vao->indices_vbo);
    bind_vbo(&vao->indices_vbo);
    vbo_store_data(&vao->indices_vbo, indices, (sizeof(int)*num_indices), usage_type);

}

void create_float_attribute( vao_t* vao, int attribute, float* data, int data_size, int attribute_size, int stride, int offset, usage_type_t usage_type )
{
    vbo_t tmp_vbo;
    tmp_vbo.type = GL_ARRAY_BUFFER;
    allocate_vbo(&tmp_vbo);
    bind_vbo(&tmp_vbo);
    vbo_store_data(&tmp_vbo, data, data_size, usage_type);
    glVertexAttribPointer(attribute, attribute_size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
    unbind_vbo(&tmp_vbo);
    vao->attribute_map.insert({ attribute, vao->vbos.size() });
    vao->vbos.push_back(tmp_vbo);
}

void create_int_attribute( vao_t* vao, int attribute, int* data, int data_size, int attribute_size, int stride, int offset, usage_type_t usage_type )
{
    vbo_t tmp_vbo;
    tmp_vbo.type = GL_ARRAY_BUFFER;
    allocate_vbo(&tmp_vbo);
    bind_vbo(&tmp_vbo);
    vbo_store_data(&tmp_vbo, data, data_size, usage_type);
    glVertexAttribPointer(attribute, attribute_size, GL_INT, GL_FALSE, (attribute_size * sizeof(int)), (void*)offset);
    unbind_vbo(&tmp_vbo);
    vao->attribute_map.insert({ attribute, vao->vbos.size() });
    vao->vbos.push_back(tmp_vbo);

}

void update_index_buffer( vao_t* vao, int* indices, int num_indices, usage_type_t usage_type )
{
    bind_vbo(&vao->indices_vbo);
    vbo_store_data(&vao->indices_vbo, indices, (sizeof(int) * num_indices), usage_type);
}

void update_float_attribute( vao_t* vao, int attribute, float* data, int data_size, usage_type_t usage_type )
{
    std::unordered_map<int, size_t>::const_iterator attr_idx = vao->attribute_map.find(attribute);
    if ( attr_idx != vao->attribute_map.end() ) {
        bind_vbo(&vao->vbos[attr_idx->second]);
        vbo_store_data(&vao->vbos[attr_idx->second], data, data_size, usage_type);
        unbind_vbo(&vao->vbos[attr_idx->second]);
    }
}

void update_int_attribute( vao_t* vao, int attribute, int* data, int data_size, usage_type_t usage_type )
{
    std::unordered_map<int, size_t>::const_iterator attr_idx = vao->attribute_map.find(attribute);
    if ( attr_idx != vao->attribute_map.end() ) {
        bind_vbo(&vao->vbos[attr_idx->second]);
        vbo_store_data(&vao->vbos[attr_idx->second], data, data_size, usage_type);
        unbind_vbo(&vao->vbos[attr_idx->second]);
    }
}

void create_float_instanced_attribute(vao_t* vao, int attribute, float* data, int data_size, int attribute_size,
                                      int stride, int offset, unsigned int divisor, usage_type_t usage_type )
{
    vbo_t tmp_vbo;
    tmp_vbo.type = GL_ARRAY_BUFFER;
    allocate_vbo(&tmp_vbo);
    bind_vbo(&tmp_vbo);
    vbo_store_data(&tmp_vbo, data, data_size, usage_type);
    glVertexAttribPointer(attribute, attribute_size, GL_FLOAT, GL_FALSE, stride, (void*)offset);
    glVertexAttribDivisor(attribute, divisor);
    unbind_vbo(&tmp_vbo);
    vao->attribute_map.insert({ attribute, vao->vbos.size() });
    vao->vbos.push_back(tmp_vbo);
}

} //end namespace core
