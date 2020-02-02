#include "vector3f.h"

namespace Engine {

const Vector3f Vector3f::BASIS_X(1.0f, 0.0f, 0.0f);
const Vector3f Vector3f::BASIS_Y(0.0f, 1.0f, 0.0f);
const Vector3f Vector3f::BASIS_Z(0.0f, 0.0f, 1.0f);
const Vector3f Vector3f::ZERO;
const Vector3f Vector3f::UNIT(1.0f, 1.0f, 1.0f);

Vector3f::Vector3f( void )
{
     x = y = z = 0;
     glm_vec = glm::vec3(0.0f);
}

Vector3f::Vector3f( float32_t x, float32_t y, float32_t z )
{
     this->x = x;
     this->y = y;
     this->z = z;
     glm_vec = glm::vec3(x, y, z);
}

Vector3f::Vector3f( float32_t value )
{
     x = y = z = value;
}

Vector3f::~Vector3f( void )
{
     // do nothing
}

Vector3f Vector3f::operator-( void ) const
{
     return Vector3f(-x, -y, -z);
}

Vector3f Vector3f::operator+( const Vector3f& vector ) const
{
     glm::vec3 tmp_vec = glm_vec + vector.glm_vec;
     LOG("GLM + x:%f y:%f z:%f", tmp_vec.x, tmp_vec.y, tmp_vec.z);
     Vector3f tmp(x + vector.x, y + vector.y, z + vector.z);
     LOG("ENGINE + x:%f y:%f z:%f", tmp.x, tmp.y, tmp.z);
     return Vector3f(x + vector.x, y + vector.y, z + vector.z);
}

Vector3f Vector3f::operator-( const Vector3f& vector ) const
{
     glm::vec3 tmp_vec = glm_vec + vector.glm_vec;
     LOG("GLM - x:%f y:%f z:%f", tmp_vec.x, tmp_vec.y, tmp_vec.z);
     Vector3f tmp(x + vector.x, y + vector.y, z + vector.z);
     LOG("ENGINE - x:%f y:%f z:%f", tmp.x, tmp.y, tmp.z);
     return Vector3f(x - vector.x, y - vector.y, z - vector.z);
}

Vector3f Vector3f::operator*( const Vector3f& vector ) const
{
     glm::vec3 tmp_vec = glm_vec * vector.glm_vec;
     LOG("GLM * x:%f y:%f z:%f", tmp_vec.x, tmp_vec.y, tmp_vec.z);
     Vector3f tmp(x * vector.x, y * vector.y, z * vector.z);
     LOG("ENGINE * x:%f y:%f z:%f", tmp.x, tmp.y, tmp.z);
     return Vector3f(x * vector.x, y * vector.y, z * vector.z);
}

Vector3f Vector3f::operator*( const float32_t value ) const
{
     glm::vec3 tmp_vec = glm_vec * value;
     LOG("GLM v* x:%f y:%f z:%f", tmp_vec.x, tmp_vec.y, tmp_vec.z);
     Vector3f tmp(x * value, y * value, z * value);
     LOG("ENGINE v* x:%f y:%f z:%f", tmp.x, tmp.y, tmp.z);
     return Vector3f(x * value, y * value, z * value);
}

Vector3f Vector3f::operator/( const Vector3f& vector ) const
{
     glm::vec3 tmp_vec = glm_vec / vector.glm_vec;
     LOG("GLM / x:%f y:%f z:%f", tmp_vec.x, tmp_vec.y, tmp_vec.z);
     Vector3f tmp(x / vector.x, y / vector.y, z / vector.z);
     LOG("ENGINE / x:%f y:%f z:%f", tmp.x, tmp.y, tmp.z);
     return Vector3f(x / vector.x, y / vector.y, z / vector.z);
}

Vector3f Vector3f::operator/( const float32_t value ) const
{
     glm::vec3 tmp_vec = glm_vec / value;
     LOG("GLM v/ x:%f y:%f z:%f", tmp_vec.x, tmp_vec.y, tmp_vec.z);
     Vector3f tmp(x / value, y / value, z / value);
     LOG("ENGINE v/ x:%f y:%f z:%f", tmp.x, tmp.y, tmp.z);
     return Vector3f(x / value, y / value, z / value);
}

Vector3f& Vector3f::operator=( const Vector3f& vector )
{
     x = vector.x;
     y = vector.y;
     z = vector.z;

     return *this;
}

Vector3f& Vector3f::operator+=( const Vector3f& vector )
{
     x += vector.x;
     y += vector.y;
     z += vector.z;

     return *this;
}

Vector3f& Vector3f::operator-=( const Vector3f& vector )
{
     x -= vector.x;
     y -= vector.y;
     z -= vector.z;

     return *this;
}

Vector3f& Vector3f::operator*=( const Vector3f& vector )
{
     x *= vector.x;
     y *= vector.y;
     z *= vector.z;

     return *this;
}

Vector3f& Vector3f::operator*=( const float32_t value )
{
     x *= value;
     y *= value;
     z *= value;

     return *this;
}

Vector3f& Vector3f::operator/=( const Vector3f& vector )
{
     x /= vector.x;
     y /= vector.y;
     z /= vector.z;

     return *this;
}

Vector3f& Vector3f::operator/=( const float32_t value )
{
     x /= value;
     y /= value;
     z /= value;

     return *this;
}

} // end namespace Engine

