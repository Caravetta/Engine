#if !defined(VBO_H)

#include "../../core_common.h"

namespace core {

    class CORE_API vbo {
    public:
        unsigned int id;
        int type;

        vbo( int type );
        ~vbo();
        void bind();
        void unbind();
        void store_data( float* data, int data_size );
        void store_data( int* data, int data_size );
    };

} //end namespace core

#define VBO_H
#endif
