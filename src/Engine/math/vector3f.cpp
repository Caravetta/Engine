#include <stdio.h>
#include <string.h>
#include <iostream>
#include <math.h>
#include "Engine.h"

namespace Engine {

Vector3f::Vector3f()
{
#if SIMD_ON
	data = _mm_set1_ps(0);
#else
	memset(&data, 0, sizeof(float) * 3);
#endif
}

Vector3f::Vector3f( const float x, const float y, const float z )
{
#if SIMD_ON
	data = _mm_set_ps(z, y, x, 0);
#else
	this->x = x;
	this->y = y;
	this->z = z;
#endif
}

Vector3f::Vector3f( const __m128 data )
{
	this->data = data;
}

bool Vector3f::compare( const Vector3f &other ) const
{
#if SIMD_ON
	return _mm_movemask_ps(_mm_cmpeq_ps(data, other.data)) == 0xF;
#else
	return ( ( x == other.x ) && ( y == other.y ) && ( z == other.z ) );
#endif
}

Vector3f Vector3f::normalize_fast() const
{
    //float length = qsqrt(x * x + y * y + z * z); //TODO: fix this
    float length = 1;
    return Vector3f(x / length, y / length, z / length);
}

Vector3f Vector3f::normalize() const
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

float &Vector3f::operator[]( const int index )
{
    return ( &x )[ index ];
}

Vector3f &Vector3f::operator=( const Vector3f &other )
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
#if SIMD_ON
    __m128 tmp_scalar = _mm_set_ps(scalar, scalar, scalar, 0);
	return Vector3f( _mm_mul_ps(data, tmp_scalar) );
#else
	return Vector3f( x * scalar, y * scalar, z * scalar );
#endif
}

Vector3f &Vector3f::operator*=( const float scalar )
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

Vector3f &Vector3f::operator/=( const float scalar )
{
    float inverted_scalar = 1.0f / scalar;
    x *= inverted_scalar;
    y *= inverted_scalar;
    z *= inverted_scalar;

    return *this;
}

Vector3f &Vector3f::operator/=( const Vector3f &other )
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

Vector3f &Vector3f::operator+=( const Vector3f &other )
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

Vector3f &Vector3f::operator-=( const Vector3f &other )
{
    x -= other.x;
    y -= other.y;
    z -= other.z;

    return *this;
}

std::ostream& operator<<(std::ostream& stream, const Vector3f& vector)
{
    stream << "vector3f:( x:" << vector.x << ", y:" << vector.y << ", z:" << vector.z << ")";
    return stream;
}

} //end namespace Engine

