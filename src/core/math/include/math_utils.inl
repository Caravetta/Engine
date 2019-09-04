
#include <math.h>
#include "vector4f.h"

namespace Engine {

#define PI 3.14159265

float32_t radians( float degree )
{
     return (float32_t)(degree * (PI/180));
}

float32_t sin( float32_t radians )
{
     return sinf(radians);
}

float32_t cos( float32_t radians )
{
     return cosf(radians);
}

float32_t tan( float32_t radians )
{
     return tanf(radians);
}

Matrix4f translate( const Vector3f& vector )
{
     Matrix4f trans = Matrix4f::IDENTITY;

     trans[3][0] = vector.x;
     trans[3][1] = vector.y;
     trans[3][2] = vector.z;

     return trans;
}

Matrix4f translate( Matrix4f matrix, Vector3f vector )
{
     //TODO(JOSH): need to fix
     Matrix4f tmp = Matrix4f::IDENTITY;

     tmp[3][0] = vector.x;
     tmp[3][1] = vector.y;
     tmp[3][2] = vector.z;


     Matrix4f trans = matrix + tmp;

     return trans;
}

Matrix4f scale( const Vector3f& vector )
{
     Matrix4f scale = Matrix4f::IDENTITY;

     scale[0][0] = vector.x == 0 ? 1 : vector.x;
     scale[1][1] = vector.y == 0 ? 1 : vector.y;
     scale[2][2] = vector.z == 0 ? 1 : vector.z;

     return scale;
}

Matrix4f rotation( const Vector3f& vector )
{
     Matrix4f rot_x = Matrix4f::IDENTITY;
     float32_t x_rad = radians(vector.x);

     rot_x[1][1] =  cos(x_rad);
     rot_x[1][2] =  sin(x_rad);
     rot_x[2][1] = -sin(x_rad);
     rot_x[2][2] =  cos(x_rad);

     Matrix4f rot_y = Matrix4f::IDENTITY;
     float32_t y_rad = radians(vector.y);

     rot_y[0][0] =  cos(y_rad);
     rot_y[0][2] = -sin(y_rad);
     rot_y[2][0] =  sin(y_rad);
     rot_y[2][2] =  cos(y_rad);

     Matrix4f rot_z = Matrix4f::IDENTITY;
     float32_t z_rad = radians(vector.z);

     rot_z[0][0] =  cos(z_rad);
     rot_z[0][1] =  sin(z_rad);
     rot_z[1][0] = -sin(z_rad);
     rot_z[1][1] =  cos(z_rad);

     return rot_x * rot_y * rot_z;
}

Matrix4f perspective_projection( float32_t fov_radians, float32_t aspect_ratio,
                                 float32_t near_clip, float32_t far_clip )
{
     float32_t x_scale = 1.0f / tan( fov_radians * 0.5f );
     float32_t y_scale = x_scale * aspect_ratio;

     float32_t z_scale = far_clip / ( far_clip - near_clip );
     float32_t t_scale = -near_clip * z_scale;

     return Matrix4f( Vector4f(x_scale, 0.0f,    0.0f,    0.0f),
                      Vector4f(0.0f,    y_scale, 0.0f,    0.0f),
                      Vector4f(0.0f,    0.0f,    z_scale, 1.0f),
                      Vector4f(0.0f,    0.0f,    t_scale, 0.0f) );
}

Matrix4f orthographic_projection( float32_t bottom, float32_t top, float32_t left,
                                  float32_t right, float32_t near_clip, float32_t far_clip )
{
     float32_t x_scale = 2 / (right - left);
     float32_t y_scale = 2 / (top - bottom);

     float32_t z_scale = -2 / (far_clip - near_clip);
     float32_t t_scale = -((far_clip + near_clip) / (far_clip - near_clip));

     float32_t x_trans = -((right + left) / (right - left));
     float32_t y_trans = -((top + bottom) / (top - bottom));

     return Matrix4f( Vector4f(x_scale, 0.0f,    0.0f,    0.0f),
                      Vector4f(0.0f,    y_scale, 0.0f,    0.0f),
                      Vector4f(0.0f,    0.0f,    z_scale, 0.0f),
                      Vector4f(x_trans, y_trans, t_scale, 1.0f) );

}

Matrix4f orthographic_projection( float32_t width, float32_t height,
                                  float32_t near_clip, float32_t far_clip )
{
     float32_t x_scale = 2.0f / width;
     float32_t y_scale = 2.0f / height;

     float32_t z_scale = 1.0f / ( far_clip - near_clip );
     float32_t t_scale = -near_clip * z_scale;

     return Matrix4f( Vector4f(x_scale, 0.0f,    0.0f,    0.0f),
                      Vector4f(0.0f,    y_scale, 0.0f,    0.0f),
                      Vector4f(0.0f,    0.0f,    z_scale, 0.0f),
                      Vector4f(0.0f,    0.0f,    t_scale, 1.0f) );
}

Matrix4f model_transform( const Vector3f& position_vec,
                          const Vector3f& scale_vec,
                          const Vector3f& rotation_vec )
{
     return translate(position_vec) * rotation(rotation_vec) * scale(scale_vec);
}

Matrix4f view_transform( const Vector3f& position_vec,
                         const Vector3f& scale_vec,
                         const Vector3f& rotation_vec )
{
     return translate(position_vec) * rotation(rotation_vec) * scale(scale_vec);
}

};
