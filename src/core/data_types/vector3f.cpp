#include <math.h>
#include "vector3f.h"

namespace Engine {

Vector3f::Vector3f( void )
{
     x = y = z = 0;
}

Vector3f::Vector3f( const float value )
{
     x = y = z = value;
}

Vector3f::Vector3f( const float x, const float y, const float z )
{
     this->x = x;
     this->y = y;
     this->z = z;
}

bool Vector3f::compare( const Vector3f &other ) const
{
     return ( ( x == other.x ) && ( y == other.y ) && ( z == other.z ) );
}

Vector3f Vector3f::normalize_fast( void ) const
{
     //TODO(JOSH): need to fix this function 4/14/2019
     //float length = qsqrt(x * x + y * y + z * z);
     float length = 1;
     return Vector3f(x / length, y / length, z / length);
}

Vector3f Vector3f::normalize( void ) const
{
     float length = sqrtf(x * x + y * y + z * z);
     return Vector3f(x / length, y / length, z / length);
}

Vector3f Vector3f::cross( const Vector3f& other )
{
     return Vector3f( y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x );
}

float Vector3f::operator[]( const int index ) const
{
     return ( &x )[ index ];
}

float& Vector3f::operator[]( const int index )
{
     return ( &x )[ index ];
}

Vector3f& Vector3f::operator=( const Vector3f &other )
{
     x = other.x;
     y = other.y;
     z = other.z;

     return *this;
}

bool Vector3f::operator==( const Vector3f &other ) const
{
     return compare( other );
}

bool Vector3f::operator!=( const Vector3f &other ) const
{
     return !compare( other );
}

Vector3f Vector3f::operator-() const
{
     return Vector3f( -x, -y, -z );
}

float Vector3f::operator*( const Vector3f &other ) const
{
     return x * other.x + y * other.y + z * other.z;
}

Vector3f Vector3f::operator*( const float scalar ) const
{
     return Vector3f( x * scalar, y * scalar, z * scalar );
}

Vector3f& Vector3f::operator*=( const float scalar )
{
     x *= scalar;
     y *= scalar;
     z *= scalar;

     return *this;
}

Vector3f Vector3f::operator/( const float scalar ) const
{
     float inverted_scalar = 1.0f / scalar;
     return Vector3f( x * inverted_scalar, y * inverted_scalar, z * inverted_scalar );
}

Vector3f& Vector3f::operator/=( const float scalar )
{
     float inverted_scalar = 1.0f / scalar;
     x *= inverted_scalar;
     y *= inverted_scalar;
     z *= inverted_scalar;

     return *this;
}

Vector3f& Vector3f::operator/=( const Vector3f &other )
{
     x /= other.x;
     y /= other.y;
     z /= other.z;

     return *this;
}

Vector3f Vector3f::operator+( const Vector3f &other ) const
{
     return Vector3f( x + other.x, y + other.y, z + other.z );
}

Vector3f& Vector3f::operator+=( const Vector3f &other )
{
     x += other.x;
     y += other.y;
     z += other.z;

     return *this;
}

Vector3f Vector3f::operator-( const Vector3f &other ) const
{
     return Vector3f( x - other.x, y - other.y, z - other.z );
}

Vector3f& Vector3f::operator-=( const Vector3f &other )
{
     x -= other.x;
     y -= other.y;
     z -= other.z;

     return *this;
}

} // end namespace Engine

