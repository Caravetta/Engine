#if !defined(FONT_H)

#include <ft2build.h>
#include FT_FREETYPE_H
#include <vector>
#include <unordered_map>
#include "../core_common.h"

namespace core {

    class CORE_API Font {
    private:
        struct char_data_t {
            float advance_x;
            float advance_y;
            float map_width;
            float map_height;
            float map_left;
            float map_top;
            float offset_x;
            float offset_y;
        };

        uint16_t uniform_tex;
        FT_Face face;

        std::vector<std::vector<Font::char_data_t>*> font_data;
        std::unordered_map<uint16_t, uint64_t> size_map;

        std::unordered_map<uint16_t, uint16_t> texture_map;
        std::unordered_map<uint16_t, uint16_t> texture_width_map;
        std::unordered_map<uint16_t, uint16_t> texture_height_map;
    public:

        Font();
        void load_font_file( std::string file_path );
        void generate_atlas( uint16_t size );
        Font::char_data_t* generate_char_data( char value, uint16_t size );
        uint16_t get_font_width( uint16_t font_size );
        uint16_t get_font_height( uint16_t font_size );
        uint16_t get_font_texture_id( uint16_t font_size );
    };

} // end namespace core

#define FONT_H
#endif
