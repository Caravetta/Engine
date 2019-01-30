#include <iostream>
#include "Engine.h"

namespace Engine {

Vector2f::Vector2f()
{
    x = 0;
    y = 0;
}

Vector2f::Vector2f( const float x, const float y )
{
    this->x = x;
    this->y = y;
}

std::ostream& operator<<(std::ostream& stream, const Vector2f& vector)
{
    stream << "vector2f:( x:" << vector.x << ", y:" << vector.y << ")";
    return stream;
}

} //end namespace Engine
