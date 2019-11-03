#include <math.h>

namespace Engine {

inline float32_t Vector3f::dot( const Vector3f& vector ) const
{
     return ((x * vector.x) + (y * vector.y) + (z * vector.z));
}

inline void Vector3f::clamp( const Vector3f& min_vector, Vector3f& max_vector )
{
     x = (x < min_vector.x) ? min_vector.x : (x > max_vector.x) ? max_vector.x : x;
     y = (y < min_vector.y) ? min_vector.y : (y > max_vector.y) ? max_vector.y : y;
     z = (z < min_vector.z) ? min_vector.z : (z > max_vector.z) ? max_vector.z : z;
}

inline Vector3f& Vector3f::normalize( void )
{
     float32_t length_sqr = (x * x) + (y * y) + (z * z);
     float32_t length = (length_sqr <= 0) ? 0 : sqrt(length_sqr);

     *this = (length > NEAR_ZERO) ? *this / length : Vector3f(0, 0, 0);

     return *this;
}

inline Vector3f Vector3f::normalized( void ) const
{
     Vector3f normalized = *this;
     return normalized.normalize();
}

inline Vector3f Vector3f::cross( const Vector3f& vector ) const
{
     return Vector3f((y * vector.z - z * vector.y),(z * vector.x - x * vector.z),(x * vector.y - y * vector.x));
}

} // end namespace Engine

