#ifndef __MATH_UTILS_H__
#define __MATH_UTILS_H__

#include "Engine.h"

namespace Engine {

float to_radians( float angle );
float dot( Vector3f vec_a, Vector3f vec_b );
Vector3f normalize( Vector3f vector );
Vector3f cross( Vector3f vec_a, Vector3f vec_b );
Matrix4f lookat( Vector3f eye, Vector3f center, Vector3f up );
Matrix4f perspective( float fov, float aspect_ratio, float near, float far );

} // end namespace Engine

#endif
