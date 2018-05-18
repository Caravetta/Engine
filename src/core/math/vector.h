#if !defined(UNHINGED_VECTOR_H)

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

    inline Vector2f::Vector2f()
    {
        this->x = this->y = 0;
    }

    inline Vector2f::Vector2f( const float x, const float y )
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

    inline Vector3f::Vector3f()
    {
        this->x = this->y = this->z = 0;
    }

    inline Vector3f::Vector3f( const float x, const float y, const float z )
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    inline bool Vector3f::compare( const Vector3f &other ) const
    {
        return ( ( x == other.x ) && ( y == other.y ) && ( z == other.z ) );
    }

    inline Vector3f Vector3f::normalize_fast() const
    {
        //float length = qsqrt(x * x + y * y + z * z); //TODO: fix this
        float length = 1;
        return Vector3f(x / length, y / length, z / length);
    }

    inline Vector3f Vector3f::normalize() const
    {
        float length = sqrtf(x * x + y * y + z * z);
        return Vector3f(x / length, y / length, z / length);
    }

    inline Vector3f Vector3f::cross( const Vector3f& other )
    {
        return Vector3f( y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x );
    }

    inline float Vector3f::operator[]( const int index ) const
    {
        return ( &x )[ index ];
    }

    inline float &Vector3f::operator[]( const int index )
    {
        return ( &x )[ index ];
    }

    inline Vector3f &Vector3f::operator=( const Vector3f &other )
    {
        x = other.x;
        y = other.y;
        z = other.z;

        return *this;
    }

    inline bool Vector3f::operator==( const Vector3f &other ) const
    {
        return compare( other );
    }

    inline bool Vector3f::operator!=( const Vector3f &other ) const
    {
        return !compare( other );
    }

    inline Vector3f Vector3f::operator-() const
    {
        return Vector3f( -x, -y, -z );
    }

    inline float Vector3f::operator*( const Vector3f &other ) const
    {
        return x * other.x + y * other.y + z * other.z;
    }

    inline Vector3f Vector3f::operator*( const float scalar ) const
    {
        return Vector3f( x * scalar, y * scalar, z * scalar );
    }

    inline Vector3f &Vector3f::operator*=( const float scalar )
    {
        x *= scalar;
        y *= scalar;
        z *= scalar;

        return *this;
    }

    inline Vector3f Vector3f::operator/( const float scalar ) const
    {
        float inverted_scalar = 1.0f / scalar;
        return Vector3f( x * inverted_scalar, y * inverted_scalar, z * inverted_scalar );
    }

    inline Vector3f &Vector3f::operator/=( const float scalar )
    {
        float inverted_scalar = 1.0f / scalar;
        x *= inverted_scalar;
        y *= inverted_scalar;
        z *= inverted_scalar;

        return *this;
    }

    inline Vector3f &Vector3f::operator/=( const Vector3f &other )
    {
        x /= other.x;
        y /= other.y;
        z /= other.z;

        return *this;
    }

    inline Vector3f Vector3f::operator+( const Vector3f &other ) const
    {
        return Vector3f( x + other.x, y + other.y, z + other.z );
    }

    inline Vector3f &Vector3f::operator+=( const Vector3f &other )
    {
        x += other.x;
        y += other.y;
        z += other.z;

        return *this;
    }

    inline Vector3f Vector3f::operator-( const Vector3f &other ) const
    {
        return Vector3f( x - other.x, y - other.y, z - other.z );
    }

    inline Vector3f &Vector3f::operator-=( const Vector3f &other )
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;

        return *this;
    }

} //end namespace core

#define UNHINGED_VECTOR_H
#endif
