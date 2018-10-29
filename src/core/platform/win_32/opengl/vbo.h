#ifndef __VBO_H__
#define __VBO_H__

namespace core {

typedef struct {
    unsigned int id;
    int type;
} vbo_t;

CORE_API void allocate_vbo( vbo_t* vbo );
CORE_API void bind_vbo( vbo_t* vbo );
CORE_API void unbind_vbo( vbo_t* vbo );
CORE_API void vbo_store_data( vbo_t* vbo, void* data, uint64_t data_size, GLenum usage );

} //end namespace core

#endif //__VBO_H__
