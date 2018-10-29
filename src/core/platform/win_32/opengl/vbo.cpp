#include "vbo.h"
#include "opengl.h"

namespace core {

void allocate_vbo( vbo_t* vbo )
{
    glGenBuffers(1, (GLuint*)&vbo->id);
}

void bind_vbo( vbo_t* vbo )
{
    glBindBuffer(vbo->type, vbo->id);
}

void unbind_vbo( vbo_t* vbo )
{
    glBindBuffer(vbo->type, 0);
}

void vbo_store_data( vbo_t* vbo, void* data, uint64_t data_size, GLenum usage )
{
    glBufferData(vbo->type, data_size, data, usage);
}

} //end namespace core
