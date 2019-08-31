
#include <math.h>
#include "vector4f.h"

namespace Engine {

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

};
