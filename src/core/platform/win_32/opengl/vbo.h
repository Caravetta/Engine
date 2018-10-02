#ifndef __VBO_H__
#define __VBO_H__

namespace core {

    class CORE_API vbo {
    public:
        unsigned int id;
        int type;

        vbo( int type );
        void bind();
        void unbind();
        void store_data( float* data, int data_size );
        void store_data( int* data, int data_size );
    };

} //end namespace core

#endif //__VBO_H__
