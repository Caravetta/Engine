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

Vector2f Vector2f::operator+( const Vector2f &other ) const
{
		return Vector2f( x + other.x, y + other.y );
}

Vector2f Vector2f::operator+=( const Vector2f &other )
{
	x += other.x;
	y += other.y;

	return *this;
}

} //end namespace Engine
