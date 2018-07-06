#include "vbo.h"
#include "opengl.h"

namespace core {

vbo::vbo( int type )
{
    this->type = type;
    glGenBuffers(1, (GLuint*)&this->id);
}

vbo::~vbo()
{
    glDeleteBuffers(1, (GLuint*)&this->id);
}

void vbo::bind()
{
    glBindBuffer(type, id);
}

void vbo::unbind()
{
    glBindBuffer(type, 0);
}

void vbo::store_data( float* data, int data_size )
{
    glBufferData(type, data_size, data, GL_STATIC_DRAW);
}

void vbo::store_data( int* data, int data_size )
{
    glBufferData(type, data_size, data, GL_STATIC_DRAW);
}

} //end namespace core
