#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

#include "core_common.h"
#include "matrix4f.h"

namespace Engine {

inline float32_t radians( float degree );

inline float32_t sin( float32_t radians );
inline float32_t cos( float32_t radians );
inline float32_t tan( float32_t radians );

inline float32_t random_float( float32_t min, float32_t max );

inline Matrix4f translate( const Vector3f& vector );
inline Matrix4f translate( Matrix4f matrix, Vector3f vector );

inline Matrix4f scale( const Vector3f& vector );

inline Matrix4f rotation( const Vector3f& vector );

inline Matrix4f perspective_projection( float32_t fov_radians, float32_t aspect_ratio,
                                        float32_t near_clip, float32_t far_clip );
inline Matrix4f orthographic_projection( float32_t bottom, float32_t top, float32_t left,
                                         float32_t right, float32_t near_clip, float32_t far_clip );
inline Matrix4f orthographic_projection( float32_t width, float32_t height,
                                         float32_t near_clip, float32_t far_clip );

inline Matrix4f model_transform( const Vector3f& position_vec,
                                 const Vector3f& scale_vec,
                                 const Vector3f& rotation_vec );

inline Matrix4f view_transform( const Vector3f& position_vec,
                                const Vector3f& scale_vec,
                                const Vector3f& rotation_vec );

} // end namespace Engine

#include "math_utils.inl"

#endif //__MATH_UTILS_H__
