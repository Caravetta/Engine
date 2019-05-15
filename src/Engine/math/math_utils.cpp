#include <math.h>
#include <cmath>
#include "math_utils.h"
#include "core_common.h"

namespace Engine {

#define PI 3.14159265

float to_radians( float angle )
{
    return (float)((angle * PI) / 180);
}

float between_two_floats( float min, float max )
{
     return min + ((float)rand() / ((float)RAND_MAX / (max - min)));
}

Matrix4f translate( Matrix4f matrix, Vector3f vector )
{
    Matrix4f result;

    result = matrix;

    result.m30 = vector.x;
    result.m31 = vector.y;
    result.m32 = vector.z;

    return result;
}

Matrix4f scale( Matrix4f matrix, Vector3f vector )
{
    Matrix4f result;

    result = matrix;

    result.m00 = vector.x;
    result.m11 = vector.y;
    result.m22 = vector.z;

    return result;
}

float mag( Vector3f vector )
{
    return abs(sqrtf((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z)));
}

Vector3f normalize( Vector3f vector )
{
    Vector3f result;

    float _mag = mag( vector );

    if ( _mag != 0 ) {
        result.x = vector.x / _mag;
        result.y = vector.y / _mag;
        result.z = vector.z / _mag;
    }

    return result;
}

float dot( Vector3f vec_a, Vector3f vec_b )
{
    return (vec_a.x * vec_b.x) + (vec_a.y * vec_b.y) + (vec_a.z * vec_b.z);
}

Vector3f cross( Vector3f vec_a, Vector3f vec_b )
{
    Vector3f result;

    result.x = (vec_a.y * vec_b.z) - (vec_a.z - vec_b.y);
    result.y = (vec_a.z * vec_b.x) - (vec_a.x - vec_b.z);
    result.z = (vec_a.x * vec_b.y) - (vec_a.y - vec_b.x);

    return result;
}

Matrix4f perspective( float fov, float aspect_ratio, float near, float far )
{
    float f = tan(fov / 2.0f);

    Matrix4f result;

    result.m00 = 1 / (aspect_ratio * f);
    result.m11 = 1 / f;
    result.m22 = -far / ( far - near );
    result.m23 = -1.0f;
    result.m32 = -( far * near ) / ( far - near );

    return result;
}

Matrix4f lookat( Vector3f eye, Vector3f center, Vector3f up )
{
    Vector3f f = normalize(center - eye);
    Vector3f s = normalize(cross(up, f));
    Vector3f u = cross(f, s);

    Matrix4f result;

    result.m00 = s.x;
    result.m10 = s.y;
    result.m20 = s.z;

    result.m01 = u.x;
    result.m11 = u.y;
    result.m21 = u.z;

    result.m02 = f.x;
    result.m12 = f.y;
    result.m22 = f.z;

    result.m30 = -dot( s, eye);
    result.m31 = -dot( u, eye);
    result.m32 = -dot( f, eye);
    result.m33 = 1;

    return result;
}

} // end namespace Engine
