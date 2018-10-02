#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>
#include "../core_common.h"

namespace core {

    /*** Vector2f ***/
    class CORE_API Vector2f {
    public:
        float x;
        float y;

        Vector2f();
        Vector2f( const float x, const float y );

        friend CORE_API std::ostream& operator<<(std::ostream& stream, const Vector2f& vector);
    };

    ALWAYS_INLINE Vector2f::Vector2f()
    {
        this->x = this->y = 0;
    }

    ALWAYS_INLINE Vector2f::Vector2f( const float x, const float y )
    {
        this->x = x;
        this->y = y;
    }

    /*** Vector3f ***/
    class CORE_API Vector3f {
    public:
        float x;
        float y;
        float z;

        Vector3f();
        Vector3f( const float x, const float y, const float z );
        bool compare( const Vector3f &other ) const;
        Vector3f normalize_fast() const;
        Vector3f normalize() const;
        Vector3f cross( const Vector3f& other );

        friend CORE_API std::ostream& operator<<(std::ostream& stream, const Vector3f& vector);

        float operator[]( const int index ) const;
        float & operator[]( const int index );
        Vector3f & operator=( const Vector3f &other );
        bool operator==( const Vector3f &other ) const;
        bool operator!=( const Vector3f &other ) const;
        Vector3f operator-() const;
        float operator*( const Vector3f &other ) const;
        Vector3f operator*( const float scalar ) const;
        Vector3f & operator*=( const float scalar );
        Vector3f  operator/( const float scalar ) const;
        Vector3f & operator/=( const float scalar );
        Vector3f & operator/=( const Vector3f &other );
        Vector3f  operator+( const Vector3f &other ) const;
        Vector3f & operator+=( const Vector3f &other );
        Vector3f  operator-( const Vector3f &other ) const;
        Vector3f & operator-=( const Vector3f &other );


    };

    ALWAYS_INLINE Vector3f::Vector3f()
    {
        this->x = this->y = this->z = 0;
    }

    ALWAYS_INLINE Vector3f::Vector3f( const float x, const float y, const float z )
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    ALWAYS_INLINE bool Vector3f::compare( const Vector3f &other ) const
    {
        return ( ( x == other.x ) && ( y == other.y ) && ( z == other.z ) );
    }

    ALWAYS_INLINE Vector3f Vector3f::normalize_fast() const
    {
        //float length = qsqrt(x * x + y * y + z * z); //TODO: fix this
        float length = 1;
        return Vector3f(x / length, y / length, z / length);
    }

    ALWAYS_INLINE Vector3f Vector3f::normalize() const
    {
        float length = sqrtf(x * x + y * y + z * z);
        return Vector3f(x / length, y / length, z / length);
    }

    ALWAYS_INLINE Vector3f Vector3f::cross( const Vector3f& other )
    {
        return Vector3f( y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x );
    }

    ALWAYS_INLINE float Vector3f::operator[]( const int index ) const
    {
        return ( &x )[ index ];
    }

    ALWAYS_INLINE float &Vector3f::operator[]( const int index )
    {
        return ( &x )[ index ];
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator=( const Vector3f &other )
    {
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    ALWAYS_INLINE bool Vector3f::operator==( const Vector3f &other ) const
    {
        return compare( other );
    }

    ALWAYS_INLINE bool Vector3f::operator!=( const Vector3f &other ) const
    {
        return !compare( other );
    }

    ALWAYS_INLINE Vector3f Vector3f::operator-() const
    {
        return Vector3f( -x, -y, -z );
    }

    ALWAYS_INLINE float Vector3f::operator*( const Vector3f &other ) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    ALWAYS_INLINE Vector3f Vector3f::operator*( const float scalar ) const
    {
        return Vector3f( x * scalar, y * scalar, z * scalar );
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator*=( const float scalar )
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    ALWAYS_INLINE Vector3f Vector3f::operator/( const float scalar ) const
    {
        float inverted_scalar = 1.0f / scalar;
        return Vector3f( x * inverted_scalar, y * inverted_scalar, z * inverted_scalar );
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator/=( const float scalar )
    {
        float inverted_scalar = 1.0f / scalar;
        x *= inverted_scalar;
        y *= inverted_scalar;
        z *= inverted_scalar;

        return *this;
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator/=( const Vector3f &other )
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;

        return *this;
    }

    ALWAYS_INLINE Vector3f Vector3f::operator+( const Vector3f &other ) const
    {
        return Vector3f( x + other.x, y + other.y, z + other.z );
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator+=( const Vector3f &other )
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    ALWAYS_INLINE Vector3f Vector3f::operator-( const Vector3f &other ) const
    {
        return Vector3f( x - other.x, y - other.y, z - other.z );
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator-=( const Vector3f &other )
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }

} //end namespace core

#endif //__VECTOR_H__
