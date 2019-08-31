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
     Matrix4f local = *this;
     Matrix4f result = Matrix4f::ZERO;

     for ( uint8_t row = 0; row < ROW_SIZE; row++ ) {
          for ( uint8_t col = 0; col < COL_SIZE; col++ ) {
               result[row][col] = local[row][col] + matrix[row][col];
          }
     }

     return result;
}

Matrix4f Matrix4f::operator*( const Matrix4f& matrix ) const
{
     Matrix4f local = *this;
     Matrix4f result = Matrix4f::ZERO;

     for ( uint8_t row = 0; row < ROW_SIZE; row++ ) {
          for ( uint8_t col = 0; col < COL_SIZE; col++ ) {
               for ( uint8_t mid = 0; mid < MID_SIZE; mid++ ) {
                    result[row][col] += local[row][mid] * matrix[mid][col];
               }
          }
     }

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

Matrix4f& Matrix4f::operator*=( const Matrix4f& matrix )
{
     Matrix4f local = *this;
     Matrix4f& result = *this;

     result = Matrix4f::ZERO;

     for ( uint8_t row = 0; row < ROW_SIZE; row++ ) {
          for ( uint8_t col = 0; col < COL_SIZE; col++ ) {
               for ( uint8_t mid = 0; mid < MID_SIZE; mid++ ) {
                    result[row][col] += local[row][mid] * matrix[mid][col];
               }
          }
     }

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

} // end namespace Engine

