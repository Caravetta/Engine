#ifndef __VECTOR3F_H__
#define __VECTOR3F_H__

#include "core_common.h"

namespace Engine {

struct Vector3f {
public:
     //META_STRUCT_DECLARE( Vector3f );
     //META_INFO_DECLARE( Vector3f );
     //static void populate_meta_struct_func( Engine::Meta_Struct& meta_struct );
     //static void populate_meta_info_func( Engine::Meta_Info& meta_info );

     const static Vector3f BASIS_X;
     const static Vector3f BASIS_Y;
     const static Vector3f BASIS_Z;
     const static Vector3f ZERO;
     const static Vector3f UNIT;

     float x;
     float y;
     float z;

     Vector3f( void );
     explicit Vector3f( float32_t x, float32_t y, float32_t z );
     explicit Vector3f( float32_t value );

     ~Vector3f( void );

     inline float32_t dot( const Vector3f& vector ) const;
     inline void clamp( const Vector3f& min_vector, Vector3f& max_vector );
     inline Vector3f& normalize( void );
     inline Vector3f normalized( void ) const;
     inline Vector3f cross( const Vector3f& vector ) const;

     Vector3f operator-( void ) const;

     Vector3f operator+( const Vector3f& vector ) const;
     Vector3f operator-( const Vector3f& vector ) const;
     Vector3f operator*( const Vector3f& vector ) const;
     Vector3f operator*( const float32_t value ) const;
     Vector3f operator/( const Vector3f& vector ) const;
     Vector3f operator/( const float32_t value ) const;

     Vector3f& operator=( const Vector3f& vector );
     Vector3f& operator+=( const Vector3f& vector );
     Vector3f& operator-=( const Vector3f& vector );
     Vector3f& operator*=( const Vector3f& vector );
     Vector3f& operator*=( const float32_t value );
     Vector3f& operator/=( const Vector3f& vector );
     Vector3f& operator/=( const float32_t value );
};

} // end namespace Engine

#include "vector3f.inl"

#endif //__VECTOR3F_H__
