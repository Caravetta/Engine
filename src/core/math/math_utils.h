#if !defined(MATH_UTILS_H)

#include <vector>
#include "../core_common.h"
#include "../image/image.h"
#include "vector.h"

namespace core {


// Note: O(nr^2) pixel error = 0
CORE_API void true_gaussian_blur( std::vector<pixel_data_t>* current_image, std::vector<pixel_data_t>* filtered_image, int width, int height, int radius );

CORE_API void fast_gaussian_blur( std::vector<pixel_data_t>* current_image, std::vector<pixel_data_t>* filtered_image, int width, int height, int radius );

CORE_API Vector3f generate_face_norm( Vector3f v0, Vector3f v1, Vector3f v2 );

CORE_API float scale_float( float input, float input_min, float input_max, float min, float max );

#define SQRT2 1.4142135623730951

inline float qsqrt( const float x )
{
    // x = [0 eeeeeeeeeee mmmmmmmmmmmmmmmmmmmmmmm]
    int i = *(int*)&x;
    int j = (((i/2-0x1fc00000)+0x3f800000)&0x3ff800000)+((i&0x7fffff)/5*2);

    float y = (*(float*)&j) * (float)((i-0x3f800000)&(0x800000) ? SQRT2 : 1); // 2-3 sig figs of significance

    // two iterations of newton: y = y - (y^2 - x)/2y yields 2^-18 points of precision
    y = (y + x/y)/2; // this yields 2^-8 points of precision
    return (y + x/y)/2;
}

inline bool aabb_collision(float rect1_x, float rect1_y, float rect1_width, float rect1_height,
                           float rect2_x, float rect2_y, float rect2_width, float rect2_height)
{
    if (rect1_x < (rect2_x + rect2_width) &&
        (rect1_x + rect1_width) > rect2_x &&
        rect1_y < (rect2_y + rect2_height) &&
        (rect1_y + rect1_height) > rect2_y ) {
        return true;
    } else {
        return false;
    }
}


} // end namespace core

#define MATH_UTILS_H
#endif
