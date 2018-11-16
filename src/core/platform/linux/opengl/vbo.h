#ifndef __VBO_H__
#define __VBO_H__

namespace core {

typedef struct {
    unsigned int id;
    int type;
} vbo_t;

void allocate_vbo( vbo_t* vbo );
void bind_vbo( vbo_t* vbo );
void unbind_vbo( vbo_t* vbo );
void vbo_store_data( vbo_t* vbo, void* data, uint64_t data_size, GLenum usage );

} //end namespace core

#endif //__VBO_H__
