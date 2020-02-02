#include "matrix4f.h"

namespace Engine {

#define ROW_SIZE 4
#define COL_SIZE 4
#define MID_SIZE 4

const Matrix4f Matrix4f::IDENTITY(Vector4f(1, 0, 0, 0),
                                  Vector4f(0, 1, 0, 0),
                                  Vector4f(0, 0, 1, 0),
                                  Vector4f(0, 0, 0, 1));
const Matrix4f Matrix4f::ZERO(Vector4f(0, 0, 0, 0),
                              Vector4f(0, 0, 0, 0),
                              Vector4f(0, 0, 0, 0),
                              Vector4f(0, 0, 0, 0));

Matrix4f::Matrix4f( void )
{
     x = Vector4f(1, 0, 0, 0);
     y = Vector4f(0, 1, 0, 0);
     z = Vector4f(0, 0, 1, 0);
     t = Vector4f(0, 0, 0, 1);
}

Matrix4f::Matrix4f( const Vector4f& x, const Vector4f& y, const Vector4f& z, const Vector4f& t )
{
     this->x = x;
     this->y = y;
     this->z = z;
     this->t = t;
}

Matrix4f::Matrix4f( const Vector3f& vector )
{
     x = Vector4f(1, 0, 0, 0);
     y = Vector4f(0, 1, 0, 0);
     z = Vector4f(0, 0, 1, 0);
     t = Vector4f(vector.x, vector.y, vector.z, 1);
}

Matrix4f::Matrix4f( const Vector4f& vector )
{
     x = Vector4f(1, 0, 0, 0);
     y = Vector4f(0, 1, 0, 0);
     z = Vector4f(0, 0, 1, 0);
     t = Vector4f(vector.x, vector.y, vector.z, vector.w);
}

Matrix4f Matrix4f::operator+( const Matrix4f& matrix ) const
{
     //TODO(JOSH): need to check this
     Matrix4f local = *this;
     Matrix4f result = Matrix4f::ZERO;

     for ( uint8_t row = 0; row < ROW_SIZE; row++ ) {
          for ( uint8_t col = 0; col < COL_SIZE; col++ ) {
               result[row][col] = local[row][col] + matrix[row][col];
          }
     }

     return result;
}

Matrix4f Matrix4f::operator*( const Matrix4f& other ) const
{
     Matrix4f m = *this;
     Matrix4f result = Matrix4f::ZERO;

     result[0][0] = (m[0][0] * other[0][0]) + (m[1][0] * other[0][1]) + (m[2][0] * other[0][2]) + (m[3][0] * other[0][3]);
     result[1][0] = (m[0][0] * other[1][0]) + (m[1][0] * other[1][1]) + (m[2][0] * other[1][2]) + (m[3][0] * other[1][3]);
     result[2][0] = (m[0][0] * other[2][0]) + (m[1][0] * other[2][1]) + (m[2][0] * other[2][2]) + (m[3][0] * other[2][3]);
     result[3][0] = (m[0][0] * other[3][0]) + (m[1][0] * other[3][1]) + (m[2][0] * other[3][2]) + (m[3][0] * other[3][3]);

     result[0][1] = (m[0][1] * other[0][0]) + (m[1][1] * other[0][1]) + (m[2][1] * other[0][2]) + (m[3][1] * other[0][3]);
     result[1][1] = (m[0][1] * other[1][0]) + (m[1][1] * other[1][1]) + (m[2][1] * other[1][2]) + (m[3][1] * other[1][3]);
     result[2][1] = (m[0][1] * other[2][0]) + (m[1][1] * other[2][1]) + (m[2][1] * other[2][2]) + (m[3][1] * other[2][3]);
     result[3][1] = (m[0][1] * other[3][0]) + (m[1][1] * other[3][1]) + (m[2][1] * other[3][2]) + (m[3][1] * other[3][3]);

     result[0][2] = (m[0][2] * other[0][0]) + (m[1][2] * other[0][1]) + (m[2][2] * other[0][2]) + (m[3][2] * other[0][3]);
     result[1][2] = (m[0][2] * other[1][0]) + (m[1][2] * other[1][1]) + (m[2][2] * other[1][2]) + (m[3][2] * other[1][3]);
     result[2][2] = (m[0][2] * other[2][0]) + (m[1][2] * other[2][1]) + (m[2][2] * other[2][2]) + (m[3][2] * other[2][3]);
     result[3][2] = (m[0][2] * other[3][0]) + (m[1][2] * other[3][1]) + (m[2][2] * other[3][2]) + (m[3][2] * other[3][3]);

     result[0][3] = (m[0][3] * other[0][0]) + (m[1][3] * other[0][1]) + (m[2][3] * other[0][2]) + (m[3][3] * other[0][3]);
     result[1][3] = (m[0][3] * other[1][0]) + (m[1][3] * other[1][1]) + (m[2][3] * other[1][2]) + (m[3][3] * other[1][3]);
     result[2][3] = (m[0][3] * other[2][0]) + (m[1][3] * other[2][1]) + (m[2][3] * other[2][2]) + (m[3][3] * other[2][3]);
     result[3][3] = (m[0][3] * other[3][0]) + (m[1][3] * other[3][1]) + (m[2][3] * other[3][2]) + (m[3][3] * other[3][3]);

     return result;
}

Vector4f Matrix4f::operator*( const Vector4f& vector ) const
{
     const Matrix4f& matrix = *this;

     return Vector4f((matrix[0][0]*vector[0]) + (matrix[1][0]*vector[1]) + (matrix[2][0]*vector[2]) + (matrix[3][0]*vector[3]),
                     (matrix[0][1]*vector[0]) + (matrix[1][1]*vector[1]) + (matrix[2][1]*vector[2]) + (matrix[3][1]*vector[3]),
                     (matrix[0][2]*vector[0]) + (matrix[1][2]*vector[1]) + (matrix[2][2]*vector[2]) + (matrix[3][2]*vector[3]),
                     (matrix[0][3]*vector[0]) + (matrix[1][3]*vector[1]) + (matrix[2][3]*vector[2]) + (matrix[3][3]*vector[3]));

}

Matrix4f Matrix4f::operator*( const float32_t value ) const
{
     return Matrix4f(x * value,
                     y * value,
                     z * value,
                     t * value);
}

Matrix4f& Matrix4f::operator=( const Matrix4f& matrix )
{
     x = matrix.x;
     y = matrix.y;
     z = matrix.z;
     t = matrix.t;

     return *this;
}

Matrix4f& Matrix4f::operator+=( const Matrix4f& matrix )
{
     //TODO(JOSH): need to check this
     Matrix4f local = *this;
     Matrix4f& result = *this;

     result = Matrix4f::ZERO;

     for ( uint8_t row = 0; row < ROW_SIZE; row++ ) {
          for ( uint8_t col = 0; col < COL_SIZE; col++ ) {
               result[row][col] = local[row][col] + matrix[row][col];
          }
     }

     return result;
}

Matrix4f& Matrix4f::operator*=( const Matrix4f& other )
{
     Matrix4f m = *this;
     Matrix4f& result = *this;

     result = Matrix4f::ZERO;

     result[0][0] = (m[0][0] * other[0][0]) + (m[1][0] * other[0][1]) + (m[2][0] * other[0][2]) + (m[3][0] * other[0][3]);
     result[1][0] = (m[0][0] * other[1][0]) + (m[1][0] * other[1][1]) + (m[2][0] * other[1][2]) + (m[3][0] * other[1][3]);
     result[2][0] = (m[0][0] * other[2][0]) + (m[1][0] * other[2][1]) + (m[2][0] * other[2][2]) + (m[3][0] * other[2][3]);
     result[3][0] = (m[0][0] * other[3][0]) + (m[1][0] * other[3][1]) + (m[2][0] * other[3][2]) + (m[3][0] * other[3][3]);

     result[0][1] = (m[0][1] * other[0][0]) + (m[1][1] * other[0][1]) + (m[2][1] * other[0][2]) + (m[3][1] * other[0][3]);
     result[1][1] = (m[0][1] * other[1][0]) + (m[1][1] * other[1][1]) + (m[2][1] * other[1][2]) + (m[3][1] * other[1][3]);
     result[2][1] = (m[0][1] * other[2][0]) + (m[1][1] * other[2][1]) + (m[2][1] * other[2][2]) + (m[3][1] * other[2][3]);
     result[3][1] = (m[0][1] * other[3][0]) + (m[1][1] * other[3][1]) + (m[2][1] * other[3][2]) + (m[3][1] * other[3][3]);

     result[0][2] = (m[0][2] * other[0][0]) + (m[1][2] * other[0][1]) + (m[2][2] * other[0][2]) + (m[3][2] * other[0][3]);
     result[1][2] = (m[0][2] * other[1][0]) + (m[1][2] * other[1][1]) + (m[2][2] * other[1][2]) + (m[3][2] * other[1][3]);
     result[2][2] = (m[0][2] * other[2][0]) + (m[1][2] * other[2][1]) + (m[2][2] * other[2][2]) + (m[3][2] * other[2][3]);
     result[3][2] = (m[0][2] * other[3][0]) + (m[1][2] * other[3][1]) + (m[2][2] * other[3][2]) + (m[3][2] * other[3][3]);

     result[0][3] = (m[0][3] * other[0][0]) + (m[1][3] * other[0][1]) + (m[2][3] * other[0][2]) + (m[3][3] * other[0][3]);
     result[1][3] = (m[0][3] * other[1][0]) + (m[1][3] * other[1][1]) + (m[2][3] * other[1][2]) + (m[3][3] * other[1][3]);
     result[2][3] = (m[0][3] * other[2][0]) + (m[1][3] * other[2][1]) + (m[2][3] * other[2][2]) + (m[3][3] * other[2][3]);
     result[3][3] = (m[0][3] * other[3][0]) + (m[1][3] * other[3][1]) + (m[2][3] * other[3][2]) + (m[3][3] * other[3][3]);

     return result;
}

Matrix4f& Matrix4f::operator*=( const float32_t value )
{
     x *= value;
     y *= value;
     z *= value;
     t *= value;

     return *this;
}

bool Matrix4f::operator==(const Matrix4f& matrix ) const
{
     return (x == matrix.x &&
             y == matrix.y &&
             z == matrix.z &&
             t == matrix.t);
}

bool Matrix4f::operator!=(const Matrix4f& matrix ) const
{
     return !(x == matrix.x &&
              y == matrix.y &&
              z == matrix.z &&
              t == matrix.t);
}

Vector4f& Matrix4f::operator[] (const uint32_t i)
{
     return (&x)[i];
}

const Vector4f& Matrix4f::operator[] (const uint32_t i) const
{
     return (&x)[i];
}

float32_t& Matrix4f::operator()(const uint32_t i, const uint32_t j)
{
     typedef float array_2d[4][4];
     array_2d& array = reinterpret_cast<array_2d&>( x );
     return array[j][i];
}

const float32_t& Matrix4f::operator()(const uint32_t i, const uint32_t j) const
{
     typedef float array_2d[4][4];
     const array_2d& array = reinterpret_cast<const array_2d&>( x );
     return array[j][i];
}

void Matrix4f::log( void )
{
     LOG("mat4x4((%f, %f, %f ,%f), (%f, %f, %f ,%f), (%f, %f, %f ,%f), (%f, %f, %f ,%f))E",
          x.x, x.y, x.z, x.w,
          y.x, y.y, y.z, y.w,
          z.x, z.y, z.z, z.w,
          t.x, t.y, t.z, t.w);
}

Matrix4f Matrix4f::inverse( void )
{
     float m[16] = {x.x, x.y, x.z, x.w,
                    y.x, y.y, y.z, y.w,
                    z.x, z.y, z.z, z.w,
                    t.x, t.y, t.z, t.w};

     float inv[16] = {0};

     float det;

     inv[0] = m[5]  * m[10] * m[15] -
             m[5]  * m[11] * m[14] -
             m[9]  * m[6]  * m[15] +
             m[9]  * m[7]  * m[14] +
             m[13] * m[6]  * m[11] -
             m[13] * m[7]  * m[10];

    inv[4] = -m[4]  * m[10] * m[15] +
              m[4]  * m[11] * m[14] +
              m[8]  * m[6]  * m[15] -
              m[8]  * m[7]  * m[14] -
              m[12] * m[6]  * m[11] +
              m[12] * m[7]  * m[10];

    inv[8] = m[4]  * m[9] * m[15] -
             m[4]  * m[11] * m[13] -
             m[8]  * m[5] * m[15] +
             m[8]  * m[7] * m[13] +
             m[12] * m[5] * m[11] -
             m[12] * m[7] * m[9];

    inv[12] = -m[4]  * m[9] * m[14] +
               m[4]  * m[10] * m[13] +
               m[8]  * m[5] * m[14] -
               m[8]  * m[6] * m[13] -
               m[12] * m[5] * m[10] +
               m[12] * m[6] * m[9];

    inv[1] = -m[1]  * m[10] * m[15] +
              m[1]  * m[11] * m[14] +
              m[9]  * m[2] * m[15] -
              m[9]  * m[3] * m[14] -
              m[13] * m[2] * m[11] +
              m[13] * m[3] * m[10];

    inv[5] = m[0]  * m[10] * m[15] -
             m[0]  * m[11] * m[14] -
             m[8]  * m[2] * m[15] +
             m[8]  * m[3] * m[14] +
             m[12] * m[2] * m[11] -
             m[12] * m[3] * m[10];

    inv[9] = -m[0]  * m[9] * m[15] +
              m[0]  * m[11] * m[13] +
              m[8]  * m[1] * m[15] -
              m[8]  * m[3] * m[13] -
              m[12] * m[1] * m[11] +
              m[12] * m[3] * m[9];

    inv[13] = m[0]  * m[9] * m[14] -
              m[0]  * m[10] * m[13] -
              m[8]  * m[1] * m[14] +
              m[8]  * m[2] * m[13] +
              m[12] * m[1] * m[10] -
              m[12] * m[2] * m[9];

    inv[2] = m[1]  * m[6] * m[15] -
             m[1]  * m[7] * m[14] -
             m[5]  * m[2] * m[15] +
             m[5]  * m[3] * m[14] +
             m[13] * m[2] * m[7] -
             m[13] * m[3] * m[6];

    inv[6] = -m[0]  * m[6] * m[15] +
              m[0]  * m[7] * m[14] +
              m[4]  * m[2] * m[15] -
              m[4]  * m[3] * m[14] -
              m[12] * m[2] * m[7] +
              m[12] * m[3] * m[6];

    inv[10] = m[0]  * m[5] * m[15] -
              m[0]  * m[7] * m[13] -
              m[4]  * m[1] * m[15] +
              m[4]  * m[3] * m[13] +
              m[12] * m[1] * m[7] -
              m[12] * m[3] * m[5];

    inv[14] = -m[0]  * m[5] * m[14] +
               m[0]  * m[6] * m[13] +
               m[4]  * m[1] * m[14] -
               m[4]  * m[2] * m[13] -
               m[12] * m[1] * m[6] +
               m[12] * m[2] * m[5];

    inv[3] = -m[1] * m[6] * m[11] +
              m[1] * m[7] * m[10] +
              m[5] * m[2] * m[11] -
              m[5] * m[3] * m[10] -
              m[9] * m[2] * m[7] +
              m[9] * m[3] * m[6];

    inv[7] = m[0] * m[6] * m[11] -
             m[0] * m[7] * m[10] -
             m[4] * m[2] * m[11] +
             m[4] * m[3] * m[10] +
             m[8] * m[2] * m[7] -
             m[8] * m[3] * m[6];

    inv[11] = -m[0] * m[5] * m[11] +
               m[0] * m[7] * m[9] +
               m[4] * m[1] * m[11] -
               m[4] * m[3] * m[9] -
               m[8] * m[1] * m[7] +
               m[8] * m[3] * m[5];

    inv[15] = m[0] * m[5] * m[10] -
              m[0] * m[6] * m[9] -
              m[4] * m[1] * m[10] +
              m[4] * m[2] * m[9] +
              m[8] * m[1] * m[6] -
              m[8] * m[2] * m[5];

     det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];

     det = 1.0f / det;

     Vector4f x((inv[0] * det), (inv[1] * det), (inv[2] * det), (inv[3] * det));
     Vector4f y((inv[4] * det), (inv[5] * det), (inv[6] * det), (inv[7] * det));
     Vector4f z((inv[8] * det), (inv[9] * det), (inv[10] * det), (inv[11] * det));
     Vector4f t((inv[12] * det), (inv[13] * det), (inv[14] * det), (inv[15] * det));

     return Matrix4f(x, y, z, t);
}

} // end namespace Engine

