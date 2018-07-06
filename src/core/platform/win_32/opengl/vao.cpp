#include "vao.h"
#include "opengl.h"

namespace core {

vao::vao()
{
    glGenVertexArrays(1, &id);
    indices_vbo = NULL;
}

vao::~vao()
{
    LOG("DELETE VAO");
    delete(indices_vbo);
    for (int i = 0; i < vbos.size(); i++) {
        delete(vbos[i]);
    }

    glDeleteBuffers(1, &id);
}

void vao::bind()
{
    glBindVertexArray(id);
}

void vao::unbind()
{
    glBindVertexArray(0);
}

void vao::bind_attributes()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
}

void vao::unbind_attributes()
{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}

void vao::create_index_buffer( int* indices, int num_indices )
{
    indices_vbo = new vbo(GL_ELEMENT_ARRAY_BUFFER);
    indices_vbo->bind();
    indices_vbo->store_data(indices, (sizeof(int)*num_indices));
}

void vao::create_attribute( int attribute, float* data, int data_size, int attribute_size )
{
    vbo* _vbo = new vbo(GL_ARRAY_BUFFER);
    _vbo->bind();
    _vbo->store_data(data, data_size);
    glVertexAttribPointer(attribute, attribute_size, GL_FLOAT, GL_FALSE, (attribute_size * sizeof(float)), (void*)0);
    _vbo->unbind();
    vbos.push_back(_vbo);
}

void vao::create_attribute( int attribute, int* data, int data_size, int attribute_size )
{
    vbo* _vbo = new vbo(GL_ARRAY_BUFFER);
    _vbo->bind();
    _vbo->store_data(data, data_size);
    glVertexAttribPointer(attribute, attribute_size, GL_INT, GL_FALSE, (attribute_size * sizeof(int)), (void*)0);
    _vbo->unbind();
    vbos.push_back(_vbo);
}

} //end namespace core
