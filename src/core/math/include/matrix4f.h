#ifndef __MATRIX4F_H__
#define __MATRIX4F_H__

#include "core_common.h"
#include "meta_struct.h"
#include "vector3f.h"
#include "vector4f.h"

namespace Engine {

struct Matrix4f : Reflection::Struct {
public:
     META_STRUCT_DECLARE( Matrix4f );
     static void populate_meta_struct_func( Engine::Meta_Struct& meta_struct );

     const static Matrix4f ZERO;
     const static Matrix4f IDENTITY;

     Vector4f x;
     Vector4f y;
     Vector4f z;
     Vector4f t;

     Matrix4f( void );
     explicit Matrix4f( const Vector4f& x, const Vector4f& y, const Vector4f& z, const Vector4f& t );
     //explicit Matrix4f( const Matrix3f& matrix );
     explicit Matrix4f( const Vector3f& vector );
     explicit Matrix4f( const Vector4f& vector );

     Matrix4f operator+( const Matrix4f& matrix ) const;
     Matrix4f operator*( const Matrix4f& other ) const;
     Vector4f operator*( const Vector4f& vector ) const;
     Matrix4f operator*( const float32_t value ) const;

     //Matrix4f& operator=( const Matrix3f& matrix );
     Matrix4f& operator=( const Matrix4f& matrix );
     Matrix4f& operator+=( const Matrix4f& matrix );
     Matrix4f& operator*=( const Matrix4f& other );
     Matrix4f& operator*=( const float32_t value );

     bool operator==(const Matrix4f& matrix ) const;
     bool operator!=(const Matrix4f& matrix ) const;

     Vector4f& operator[] (const uint32_t i);
     const Vector4f& operator[] (const uint32_t i) const;
     float32_t& operator()(const uint32_t i, const uint32_t j);
     const float32_t& operator()(const uint32_t i, const uint32_t j) const;
};

} // end namespace Engine

#include "matrix4f.inl"

#endif //__MATRIX4F_H__
