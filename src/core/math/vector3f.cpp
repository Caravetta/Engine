#include "vector3f.h"

namespace Engine {

META_STRUCT_DEFINE( Vector3f );

const Vector3f Vector3f::BASIS_X(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::BASIS_Y(0.0f, 1.0f, 0.0f);
const Vector3f Vector3f::BASIS_Z(0.0f, 0.0f, 1.0f);
const Vector3f Vector3f::ZERO;
const Vector3f Vector3f::UNIT(1.0f, 1.0f, 1.0f);

void Vector3f::populate_meta_struct_func( Engine::Meta_Struct& meta_struct )
{
     meta_struct.add_field(&Vector3f::x, "x");
     meta_struct.add_field(&Vector3f::y, "y");
     meta_struct.add_field(&Vector3f::z, "z");
}

Vector3f::Vector3f( void )
{
     x = y = z = 0;
}

Vector3f::Vector3f( float32_t x, float32_t y, float32_t z )
{
     this->x = x;
     this->y = y;
     this->z = z;
}

Vector3f::Vector3f( float32_t value )
{
     x = y = z = value;
}

Vector3f::~Vector3f( void )
{
     // do nothing
}

Vector3f Vector3f::operator-( void ) const
{
     return Vector3f(-x, -y, -z);
}

Vector3f Vector3f::operator+( const Vector3f& vector ) const
{
     return Vector3f(x + vector.x, y + vector.y, z + vector.z);
}

Vector3f Vector3f::operator-( const Vector3f& vector ) const
{
     return Vector3f(x - vector.x, y - vector.y, z - vector.z);
}

Vector3f Vector3f::operator*( const Vector3f& vector ) const
{
     return Vector3f(x * vector.x, y * vector.y, z * vector.z);
}

Vector3f Vector3f::operator*( const float32_t value ) const
{
     return Vector3f(x * value, y * value, z * value);
}

Vector3f Vector3f::operator/( const Vector3f& vector ) const
{
     return Vector3f(x / vector.x, y / vector.y, z / vector.z);
}

Vector3f Vector3f::operator/( const float32_t value ) const
{
     return Vector3f(x / value, y / value, z / value);
}

Vector3f& Vector3f::operator=( const Vector3f& vector )
{
     x = vector.x;
     y = vector.y;
     z = vector.z;

     return *this;
}

Vector3f& Vector3f::operator+=( const Vector3f& vector )
{
     x += vector.x;
     y += vector.y;
     z += vector.z;

     return *this;
}

Vector3f& Vector3f::operator-=( const Vector3f& vector )
{
     x -= vector.x;
     y -= vector.y;
     z -= vector.z;

     return *this;
}

Vector3f& Vector3f::operator*=( const Vector3f& vector )
{
     x *= vector.x;
     y *= vector.y;
     z *= vector.z;

     return *this;
}

Vector3f& Vector3f::operator*=( const float32_t value )
{
     x *= value;
     y *= value;
     z *= value;

     return *this;
}

Vector3f& Vector3f::operator/=( const Vector3f& vector )
{
     x /= vector.x;
     y /= vector.y;
     z /= vector.z;

     return *this;
}

Vector3f& Vector3f::operator/=( const float32_t value )
{
     x /= value;
     y /= value;
     z /= value;

     return *this;
}

} // end namespace Engine

