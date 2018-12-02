#include <algorithm>
#include "font.h"
#include "font_manager.h"
#include "platform.h"

#define MAXWIDTH 1024

namespace Engine {

Font::Font()
{

}

void Font::load_font_file( std::string file_path )
{
    if ( FT_New_Face(Font_Manager::get_instance()->ft, file_path.c_str(), 0, &face) ) {
         LOG_ERROR("Could not open font " << file_path);
    }

}

void Font::generate_atlas( uint16_t size )
{
    FT_Set_Pixel_Sizes(face, 0, size);
    FT_GlyphSlot g = face->glyph;

    std::vector<Font::char_data_t>* tmp_vec = new std::vector<Font::char_data_t>(128);

    uint16_t w = 0;
    uint16_t h = 0;

    uint16_t roww = 0;
    uint16_t rowh = 0;
    uint16_t tex;

    for (int i = 32; i < 128; i++) {
        if ( FT_Load_Char(face, i, FT_LOAD_RENDER) ) {
             LOG_ERROR("Loading character " << (char)i << " failed");
             continue;
        }
        if ( roww + g->bitmap.width + 1 >= 1024 ) {
             w = (std::max)(w, roww);
             h += rowh;
             roww = 0;
             rowh = 0;
        }
        roww += (uint16_t)g->bitmap.width + 1;
        rowh = (std::max)(rowh, (uint16_t)g->bitmap.rows);
    }

    w = (std::max)(w, roww);
    h += rowh;

    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, (GLuint *)&tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glUniform1i(uniform_tex, 0);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, w, h, 0, GL_RED, GL_UNSIGNED_BYTE, 0);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int ox = 0;
    int oy = 0;

    rowh = 0;

    for (int i = 32; i < 128; i++) {
            if (FT_Load_Char(face, i, FT_LOAD_RENDER)) {
                LOG_ERROR("Loading character " << (char)i << "failed!");
                continue;
            }

            if (ox + g->bitmap.width + 1 >= MAXWIDTH) {
                oy += rowh;
                rowh = 0;
                ox = 0;
            }

            glTexSubImage2D(GL_TEXTURE_2D, 0, ox, oy, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);
            tmp_vec->at(i).advance_x = (float)(g->advance.x >> 6);
            tmp_vec->at(i).advance_y = (float)(g->advance.y >> 6);

            tmp_vec->at(i).map_width = (float)g->bitmap.width;
            tmp_vec->at(i).map_height = (float)g->bitmap.rows;

            tmp_vec->at(i).map_left = (float)g->bitmap_left;
            tmp_vec->at(i).map_top = (float)g->bitmap_top;

            tmp_vec->at(i).offset_x = ox / (float)w;
            tmp_vec->at(i).offset_y = oy / (float)h;

            rowh = (std::max)(rowh, (uint16_t)g->bitmap.rows);
            ox += g->bitmap.width + 1;
    }

    //int x = 0;

    font_data.push_back(tmp_vec);
    size_map.insert({ size, (font_data.size() - 1) });

    LOG("Generated a " << w << " x " << h << " (" << w * h << " kb) texture atlas for size " << size);

    //this->text_width = w;
    //this->text_height = h;
    texture_width_map.insert({ size, w});
    texture_height_map.insert({ size, h});
    texture_map.insert({ size, tex });
}

Font::char_data_t* Font::generate_char_data( char value, uint16_t size )
{
    // check to see if we have the atlas all ready
    std::unordered_map<uint16_t, uint64_t>::const_iterator ele = size_map.find(size);
    if ( ele == size_map.end() ) {
        generate_atlas(size);
        ele = size_map.find(size);
    }

    Font::char_data_t* char_data = &font_data[ele->second]->at(value);

    return char_data;
}

uint16_t Font::get_font_texture_id( uint16_t font_size )
{
    std::unordered_map<uint16_t, uint16_t>::const_iterator ele = texture_map.find(font_size);
    if ( ele == texture_map.end() ) {
        return 0;
    }

    return ele->second;
}

uint16_t Font::get_font_width( uint16_t font_size )
{
    std::unordered_map<uint16_t, uint16_t>::const_iterator ele = texture_width_map.find(font_size);
    if ( ele == texture_width_map.end() ) {
        return 0;
    }

    return ele->second;
}

uint16_t Font::get_font_height( uint16_t font_size )
{
    std::unordered_map<uint16_t, uint16_t>::const_iterator ele = texture_height_map.find(font_size);
    if ( ele == texture_height_map.end() ) {
        return 0;
    }

    return ele->second;
}

} // end namespace Engine
