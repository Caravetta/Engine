#ifndef __VECTOR3F_H__
#define __VECTOR3F_H__

#include "core_common.h"

namespace Engine {

struct ENGINE_API Vector3f {
     union {
          struct {
               float x;
               float y;
               float z;
          };
          struct {
               float r;
               float g;
               float b;
          };
     };

     Vector3f( void );
     Vector3f( const float value );
     Vector3f( const float x, const float y, const float z);

     bool compare( const Vector3f &other ) const;
     Vector3f normalize_fast( void ) const;
     Vector3f normalize( void ) const;
     Vector3f cross( const Vector3f& other );

     float operator[]( const int index ) const;
     float& operator[]( const int index );
     Vector3f& operator=( const Vector3f &other );
     bool operator==( const Vector3f &other ) const;
     bool operator!=( const Vector3f &other ) const;
     Vector3f operator-() const;
     float operator*( const Vector3f &other ) const;
     Vector3f operator*( const float scalar ) const;
     Vector3f& operator*=( const float scalar );
     Vector3f operator/( const float scalar ) const;
     Vector3f& operator/=( const float scalar );
     Vector3f& operator/=( const Vector3f &other );
     Vector3f operator+( const Vector3f &other ) const;
     Vector3f& operator+=( const Vector3f &other );
     Vector3f operator-( const Vector3f &other ) const;
     Vector3f& operator-=( const Vector3f &other );
};

} // end namespace Engine

#endif //__VECTOR3F_H__
