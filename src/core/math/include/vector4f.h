#ifndef __VECTOR4F_H__
#define __VECTOR4F_H__

#include "core_common.h"
#include "meta_struct.h"
#include "vector3f.h"

namespace Engine {

struct Vector4f : Reflection::Struct {
public:
     META_STRUCT_DECLARE( Vector4f );
     static void populate_meta_struct_func( Engine::Meta_Struct& meta_struct );

     const static Vector4f BASIS_X;
     const static Vector4f BASIS_Y;
     const static Vector4f BASIS_Z;
     const static Vector4f BASIS_W;
     const static Vector4f ZERO;
     const static Vector4f POINT;

     float x;
     float y;
     float z;
     float w;

     Vector4f( void );
     explicit Vector4f( float32_t x, float32_t y, float32_t z, float32_t w );
     explicit Vector4f( const Vector3f& vector );
     explicit Vector4f( float32_t value );

     ~Vector4f( void );

     inline float32_t dot( const Vector4f& vector ) const;
     inline void clamp( const Vector4f& min_vector, Vector4f& max_vector );
     inline Vector4f& normalize( void );
     inline Vector4f normalized( void ) const;
     inline Vector4f cross( const Vector4f& vector ) const;
     inline bool equal( const Vector4f& vector, float32_t error = 0 ) const;
     //TODO(JOSH): add in is finite
     //TODO(JOSH): add in transform

     Vector4f operator-( void ) const;

     Vector4f operator+( const Vector4f& vector ) const;
     Vector4f operator-( const Vector4f& vector ) const;
     Vector4f operator*( const Vector4f& vector ) const;
     Vector4f operator*( const float32_t value ) const;
     Vector4f operator/( const Vector4f& vector ) const;
     Vector4f operator/( const float32_t value ) const;

     Vector4f& operator=( const Vector4f& vector );
     Vector4f& operator=( const Vector3f& vector );
     Vector4f& operator+=( const Vector4f& vector );
     Vector4f& operator-=( const Vector4f& vector );
     Vector4f& operator*=( const Vector4f& vector );
     Vector4f& operator*=( const float32_t value );
     Vector4f& operator/=( const Vector4f& vector );
     Vector4f& operator/=( const float32_t value );

     bool operator==( const Vector4f& vector ) const;
     bool operator!=( const Vector4f& vector ) const;

     float32_t& operator[] ( const uint32_t i );
     const float32_t& operator[] ( const uint32_t i ) const;
};

} // end namespace Engine

#include "vector4f.inl"

#endif //__VECTOR4F_H__
