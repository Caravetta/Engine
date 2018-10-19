#include "vector.h"

namespace core {

std::ostream& operator<<(std::ostream& stream, const Vector2f& vector)
{
    stream << "vector2f:( x:" << vector.x << ", y:" << vector.y << ")";
    return stream;
}

std::ostream& operator<<(std::ostream& stream, const Vector3f& vector)
{
    stream << "vector3f:( x:" << vector.vec.x << ", y:" << vector.vec.y << ", z:" << vector.vec.z << ")";
    return stream;
}

} //end namespace core
