#include <math.h>
#include "math_utils.h"

namespace core {

void true_gaussian_blur( std::vector<pixel_data_t>* current_image, std::vector<pixel_data_t>* filtered_image,
                         int width, int height, int radius )
{
    int rs = (int)ceil(radius * 2.57);
    for ( int i = 0; i < height; i++ ) {
        for ( int j = 0; j < width; j++ ) {
            int val_r = 0;
            int wsum_r = 0;
            int val_g = 0;
            int wsum_g = 0;
            int val_b = 0;
            int wsum_b = 0;
            for (int iy = i-rs; iy < (i+rs+1); iy++) {
                for (int ix = j-rs; ix < (j+rs+1); ix++) {
                    int x = (int)fmin((float)(width-1), fmax(0.0f, (float)ix));
                    int y = (int)fmin((float)(height-1), fmax(0.0f, (float)iy));
                    int dsq = (ix-j)*(ix-j)+(iy-i)*(iy-i);
                    double pi = 3.1415926535897;
                    float wght = (float)(exp(-dsq / (2*radius*radius)) / (pi*2*radius*radius));
                    val_r += (int)(current_image->at(y*width+x).r * wght);
                    wsum_r += (int)(wght);
                    val_g += (int)(current_image->at(y*width+x).g * wght);
                    wsum_g += (int)(wght);
                    val_b += (int)(current_image->at(y*width+x).b * wght);
                    wsum_b += (int)(wght);
                }
                if (wsum_r != 0) {
                     filtered_image->at(i*width+j).r = (uint8_t)round(val_r/wsum_r);
                } else {
                     filtered_image->at(i*width+j).r = 0;
                }
                if (wsum_g != 0) {
                     filtered_image->at(i*width+j).g = (uint8_t)round(val_g/wsum_g);
                } else {
                     filtered_image->at(i*width+j).g = 0;
                }
                if (wsum_b != 0) {
                     filtered_image->at(i*width+j).b = (uint8_t)round(val_b/wsum_b);
                } else {
                     filtered_image->at(i*width+j).b = 0;
                }
            }
        }
    }
}

void fast_gaussian_blur( std::vector<pixel_data_t>* current_image, std::vector<pixel_data_t>* filtered_image,
                         int width, int height, int radius )
{

}

Vector3f generate_face_norm( Vector3f v0, Vector3f v1, Vector3f v2 )
{
    Vector3f a = v1 - v0;
    Vector3f b = v2 - v0;
    Vector3f cross = b.cross(a);

    return cross.normalize();
}

float scale_float( float input, float input_min, float input_max, float min, float max )
{
    return min + ((max - min) / (input_max - input_min)) * (input - input_min);
}

} // end namespace core
