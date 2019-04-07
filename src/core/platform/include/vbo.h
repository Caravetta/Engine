#ifndef __VBO_H__
#define __VBO_H__

#include "platform.h"
#include "core_common.h"

namespace Engine {

typedef struct {
    unsigned int id;
    int type;
} vbo_t;

void allocate_vbo( vbo_t* vbo );
void bind_vbo( vbo_t* vbo );
void unbind_vbo( vbo_t* vbo );
void vbo_store_data( vbo_t* vbo, void* data, uint64_t data_size, GLenum usage );

} //end namespace Engine

#endif //__VBO_H__
