#include "vector4f.h"

namespace Engine {

const Vector4f Vector4f::BASIS_X(1.0, 0.0, 0.0, 0.0);
const Vector4f Vector4f::BASIS_Y(0.0, 1.0, 0.0, 0.0);
const Vector4f Vector4f::BASIS_Z(0.0, 0.0, 1.0, 0.0);
const Vector4f Vector4f::BASIS_W(0.0, 0.0, 0.0, 1.0);
const Vector4f Vector4f::ZERO;
const Vector4f Vector4f::POINT (0.0, 0.0, 0.0, 1.0);

void Vector4f::populate_meta_struct_func( Engine::Meta_Struct& meta_struct )
{
     meta_struct.add_field(&Vector4f::x, "x");
     meta_struct.add_field(&Vector4f::y, "y");
     meta_struct.add_field(&Vector4f::z, "z");
     meta_struct.add_field(&Vector4f::w, "w");
}

Vector4f::Vector4f( void )
{
     x = y = z = w = 0;
}

Vector4f::Vector4f( float32_t x, float32_t y, float32_t z, float32_t w )
{
     this->x = x;
     this->y = y;
     this->z = z;
     this->w = w;
}

Vector4f::Vector4f( const Vector3f& vector )
{
     x = vector.x;
     y = vector.y;
     z = vector.z;
     w = 0;
}

Vector4f::Vector4f( float32_t value )
{
     x = y = z = w = value;
}

Vector4f::~Vector4f( void )
{
     //do nothing
}

Vector4f Vector4f::operator-( void ) const
{
     return Vector4f(-x, -y, -z, -w);
}

Vector4f Vector4f::operator+( const Vector4f& vector ) const
{
     return Vector4f(x + vector.x,
                     y + vector.y,
                     z + vector.z,
                     w + vector.w);
}

Vector4f Vector4f::operator-( const Vector4f& vector ) const
{
     return Vector4f(x - vector.x,
                     y - vector.y,
                     z - vector.z,
                     w - vector.w);
}

Vector4f Vector4f::operator*( const Vector4f& vector ) const
{
     return Vector4f(x * vector.x,
                     y * vector.y,
                     z * vector.z,
                     w * vector.w);
}

Vector4f Vector4f::operator*( const float32_t value ) const
{
     return Vector4f(x * value,
                     y * value,
                     z * value,
                     w * value);
}

Vector4f Vector4f::operator/( const Vector4f& vector ) const
{
     return Vector4f(x / vector.x,
                     y / vector.y,
                     z / vector.z,
                     w / vector.w);
}

Vector4f Vector4f::operator/( const float32_t value ) const
{
     return Vector4f(x / value,
                     y / value,
                     z / value,
                     w / value);
}

Vector4f& Vector4f::operator=( const Vector4f& vector )
{
     x = vector.x;
     y = vector.y;
     z = vector.z;
     w = vector.w;

     return *this;
}

Vector4f& Vector4f::operator=( const Vector3f& vector )
{
     x = vector.x;
     y = vector.y;
     z = vector.z;

     return *this;
}

Vector4f& Vector4f::operator+=( const Vector4f& vector )
{
     x += vector.x;
     y += vector.y;
     z += vector.z;
     w += vector.w;

     return *this;
}

Vector4f& Vector4f::operator-=( const Vector4f& vector )
{
     x -= vector.x;
     y -= vector.y;
     z -= vector.z;
     w -= vector.w;

     return *this;
}

Vector4f& Vector4f::operator*=( const Vector4f& vector )
{
     x *= vector.x;
     y *= vector.y;
     z *= vector.z;
     w *= vector.w;

     return *this;
}

Vector4f& Vector4f::operator*=( const float32_t value )
{
     x *= value;
     y *= value;
     z *= value;
     w *= value;

     return *this;
}

Vector4f& Vector4f::operator/=( const Vector4f& vector )
{
     x /= vector.x;
     y /= vector.y;
     z /= vector.z;
     w /= vector.w;

     return *this;
}

Vector4f& Vector4f::operator/=( const float32_t value )
{
     x /= value;
     y /= value;
     z /= value;
     w /= value;

     return *this;
}

bool Vector4f::operator==( const Vector4f& vector ) const
{
     return (x == vector.x &&
             y == vector.y &&
             z == vector.z &&
             w == vector.w);
}

bool Vector4f::operator!=( const Vector4f& vector ) const
{
     return !(x == vector.x &&
              y == vector.y &&
              z == vector.z &&
              w == vector.w);
}

float32_t& Vector4f::operator[] ( const uint32_t i )
{
     return (&x)[i];
}

const float32_t& Vector4f::operator[] ( const uint32_t i ) const
{
     return (&x)[i];
}

} // end namespace Engine

