#ifndef __MATRIX_H__
#define __MATRIX_H__

#include "../core_common.h"
#include "vector.h"

namespace core {

    class CORE_API Matrix4f {
    public:
        union {
            struct {
                float m00, m01, m02, m03;
            };
            __m128 row_0;
        };
        union {
            struct {
                float m10, m11, m12, m13;
            };
            __m128 row_1;
        };
        union {
            struct {
                float m20, m21, m22, m23;
            };
            __m128 row_2;
        };
        union {
            struct {
                float m30, m31, m32, m33;
            };
            __m128 row_3;
        };

        Matrix4f();
        void identity();
        void translate( Vector3f* vec );
        void rotate( float angle, Vector3f* axis );
        void scale( float scale );

        friend CORE_API std::ostream& operator<<( std::ostream &strm, const Matrix4f &a );
    };

} //end namespace core

#endif //__MATRIX_H__
