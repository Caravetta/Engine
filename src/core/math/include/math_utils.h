#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

#include "core_common.h"
#include "matrix4f.h"

namespace Engine {

inline float32_t radians( float degree );

inline float32_t sin( float32_t radians );
inline float32_t cos( float32_t radians );
inline float32_t tan( float32_t radians );

inline Matrix4f translate( Vector3f vector );
inline Matrix4f translate( Matrix4f matrix, Vector3f vector );

inline Matrix4f scale( Vector3f vector );

inline Matrix4f rotation( Vector3f vector );

inline Matrix4f perspective_projection( float32_t fov_radians, float32_t aspect_ratio,
                                        float32_t near_clip, float32_t far_clip );
inline Matrix4f orthographic_projection( float32_t bottom, float32_t top, float32_t left,
                                         float32_t right, float32_t near_clip, float32_t far_clip );
inline Matrix4f orthographic_projection( float32_t width, float32_t height,
                                         float32_t near_clip, float32_t far_clip );

} // end namespace Engine

#include "math_utils.inl"

#endif //__MATH_UTILS_H__
