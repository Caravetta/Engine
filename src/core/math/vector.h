#ifndef __VECTOR_H__
#define __VECTOR_H__

#include <math.h>
#include <xmmintrin.h>
#include "../core_common.h"

#define SIMD_ON 1

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

    typedef union {
        struct {
            float pad;
            float x;
            float y;
            float z;
        };
        __m128 data;
    } vec_3f;

    class CORE_API Vector3f {
    public:
        vec_3f vec;

        Vector3f();
        Vector3f( const float x, const float y, const float z );
        Vector3f( const __m128 data );
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
#if SIMD_ON
        vec.data = _mm_set1_ps(0);
#else
        memset(&vec, 0, sizeof(vec_3f));
#endif
    }

    ALWAYS_INLINE Vector3f::Vector3f( const float x, const float y, const float z )
    {
#if SIMD_ON
        vec.data = _mm_set_ps(z, y, x, 0);
#else
        vec.x = x;
        vec.y = y;
        vec.z = z;
#endif
    }
    ALWAYS_INLINE Vector3f::Vector3f( const __m128 data )
    {
        vec.data = data;
    }

    ALWAYS_INLINE bool Vector3f::compare( const Vector3f &other ) const
    {
#if SIMD_ON
        return _mm_movemask_ps(_mm_cmpeq_ps(vec.data, other.vec.data)) == 0xF;
#else
        return ( ( vec.x == other.vec.x ) && ( vec.y == other.vec.y ) && ( vec.z == other.vec.z ) );
#endif
    }

    ALWAYS_INLINE Vector3f Vector3f::normalize_fast() const
    {
        //float length = qsqrt(x * x + y * y + z * z); //TODO: fix this
        float length = 1;
        return Vector3f(vec.x / length, vec.y / length, vec.z / length);
    }

    ALWAYS_INLINE Vector3f Vector3f::normalize() const
    {
        float length = sqrtf(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
        return Vector3f(vec.x / length, vec.y / length, vec.z / length);
    }

    ALWAYS_INLINE Vector3f Vector3f::cross( const Vector3f& other )
    {
        return Vector3f( vec.y * other.vec.z - vec.z * other.vec.y, vec.z * other.vec.x - vec.x * other.vec.z, vec.x * other.vec.y - vec.y * other.vec.x );
    }

    ALWAYS_INLINE float Vector3f::operator[]( const int index ) const
    {
        return ( &vec.x )[ index ];
    }

    ALWAYS_INLINE float &Vector3f::operator[]( const int index )
    {
        return ( &vec.x )[ index ];
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator=( const Vector3f &other )
    {
        vec.x = other.vec.x;
        vec.y = other.vec.y;
        vec.z = other.vec.z;

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
        return Vector3f( -vec.x, -vec.y, -vec.z );
    }

    ALWAYS_INLINE float Vector3f::operator*( const Vector3f &other ) const
    {
        return vec.x * other.vec.x + vec.y * other.vec.y + vec.z * other.vec.z;
    }

    ALWAYS_INLINE Vector3f Vector3f::operator*( const float scalar ) const
    {
#if SIMD_ON
        __m128 tmp_scalar = _mm_set_ps(scalar, scalar, scalar, 0);
        return Vector3f( _mm_mul_ps(vec.data, tmp_scalar) );
#else
        return Vector3f( vec.x * scalar, vec.y * scalar, vec.z * scalar );
#endif
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator*=( const float scalar )
    {
        vec.x *= scalar;
        vec.y *= scalar;
        vec.z *= scalar;

        return *this;
    }

    ALWAYS_INLINE Vector3f Vector3f::operator/( const float scalar ) const
    {
        float inverted_scalar = 1.0f / scalar;
        return Vector3f( vec.x * inverted_scalar, vec.y * inverted_scalar, vec.z * inverted_scalar );
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator/=( const float scalar )
    {
        float inverted_scalar = 1.0f / scalar;
        vec.x *= inverted_scalar;
        vec.y *= inverted_scalar;
        vec.z *= inverted_scalar;

        return *this;
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator/=( const Vector3f &other )
    {
        vec.x /= other.vec.x;
        vec.y /= other.vec.y;
        vec.z /= other.vec.z;

        return *this;
    }

    ALWAYS_INLINE Vector3f Vector3f::operator+( const Vector3f &other ) const
    {
        return Vector3f( vec.x + other.vec.x, vec.y + other.vec.y, vec.z + other.vec.z );
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator+=( const Vector3f &other )
    {
        vec.x += other.vec.x;
        vec.y += other.vec.y;
        vec.z += other.vec.z;

        return *this;
    }

    ALWAYS_INLINE Vector3f Vector3f::operator-( const Vector3f &other ) const
    {
        return Vector3f( vec.x - other.vec.x, vec.y - other.vec.y, vec.z - other.vec.z );
    }

    ALWAYS_INLINE Vector3f &Vector3f::operator-=( const Vector3f &other )
    {
        vec.x -= other.vec.x;
        vec.y -= other.vec.y;
        vec.z -= other.vec.z;

        return *this;
    }

} //end namespace core

#endif //__VECTOR_H__
