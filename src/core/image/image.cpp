#include "image.h"
#include "tga.h"

namespace core {

Image::Image( std::string image_path )
{
    std::string file_type = image_path.substr(image_path.find_last_of(".") + 1);

    if( file_type == "tga" ) {
        load_tga(this, image_path);
    }
}

pixel_data_t Image::get_RGB(int x, int y)
{
    pixel_data_t data;

    if ( x < 0 || x >= width || y < 0 || y >= height ) {
        data.color = 0;
        return data;
    }

    uint32_t offset = 3;
    data.r = pixel_data[(y * width * offset) + (x * offset)];
    data.g = pixel_data[(y * width * offset) + (x * offset) + 1];
    data.b = pixel_data[(y * width * offset) + (x * offset) + 2];

    return data;
}

} // end namespace core
