#if !defined(VBO_H)

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

#define VBO_H
#endif
