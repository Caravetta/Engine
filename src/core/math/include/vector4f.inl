
namespace Engine {

float32_t Vector4f::dot( const Vector4f& vector ) const
{
     return (x * vector.x + y * vector.y + z * vector.z + w * vector.w);
}

void Vector4f::clamp( const Vector4f& min_vector, Vector4f& max_vector )
{
     x = (x < min_vector.x) ? min_vector.x : (x > max_vector.x) ? max_vector.x : x;
     y = (y < min_vector.y) ? min_vector.y : (y > max_vector.y) ? max_vector.y : y;
     z = (z < min_vector.z) ? min_vector.z : (z > max_vector.z) ? max_vector.z : z;
     w = (w < min_vector.w) ? min_vector.w : (w > max_vector.w) ? max_vector.w : w;
}

Vector4f& Vector4f::normalize( void )
{
     float32_t len_sqr = x * x + y * y + z * z + w * w;

     float32_t len = (len_sqr <= 0) ? 0 : sqrt(len_sqr);

     return (len > NEAR_ZERO) ? (*this /= len) : (*this = Vector4f(0, 0, 0, 0));
}

Vector4f Vector4f::normalized( void ) const
{
     Vector4f normalized = *this;
     return normalized.normalize();
}

Vector4f Vector4f::cross( const Vector4f& vector ) const
{
     return Vector4f(y*vector.z - z*vector.y, z*vector.x - x*vector.z, x*vector.y - y*vector.x, 0);
}

bool Vector4f::equal( const Vector4f& vector, float32_t error ) const
{
     return (fabs(x - vector.x) <= error &&
             fabs(y - vector.y) <= error &&
             fabs(z - vector.z) <= error &&
             fabs(w - vector.w) <= error);
}

} // end namespace Engine
