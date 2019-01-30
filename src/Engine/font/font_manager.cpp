#include <vector>
#include <unordered_map>
#include <ft2build.h>
#include FT_FREETYPE_H
#include "font_manager.h"
#include "font.h"
#include "core_common.h"
#include "Engine.h"

namespace Engine {
namespace Font_Manager {

#define FONT_RESIZE_SIZE 10

FT_Library ft;
std::vector<Font_Handle> font_handles;
std::vector<uint32_t> free_handles;
std::vector<Font> loaded_fonts;
uint32_t next_idx;
std::unordered_map<std::string, uint32_t> font_map; //maps font name to

void init()
{
    if ( FT_Init_FreeType(&ft) ) {
         LOG_ERROR("Could not init freetype library");
         return;
    }

    font_handles.resize(FONT_RESIZE_SIZE);

    for ( uint32_t ii = 0; ii < font_handles.size(); ++ii ) {
        font_handles[ii].phase = 0;
        font_handles[ii].index = ii;
    }

    loaded_fonts.resize(FONT_RESIZE_SIZE);

    next_idx = 0;
}

Font_Handle load_font_file( std::string file_path )
{
    uint32_t handle_idx;

    if ( free_handles.empty() ) {
        uint32_t current_size = (uint32_t)font_handles.size();
        if ( current_size == next_idx ) {
            font_handles.resize(current_size + FONT_RESIZE_SIZE);

            for ( uint32_t ii = current_size; ii < font_handles.size(); ++ii ) {
                font_handles[ii].phase = 0;
                font_handles[ii].index = ii;
            }

            loaded_fonts.resize(current_size + FONT_RESIZE_SIZE);
        }

        handle_idx = next_idx++;
    } else {
        handle_idx = free_handles.back();
        free_handles.pop_back();
    }

    loaded_fonts[handle_idx].load_font_file(file_path, &ft);

    return font_handles[handle_idx];
}

uint32_t get_texture_id( Font_Handle handle, uint16_t font_size )
{
    return loaded_fonts[handle.index].get_font_texture_id(font_size);
}

} // end namespace Font_Manager

uint32_t get_font_texture_id( Font_Handle handle, uint16_t font_size )
{
    return Font_Manager::loaded_fonts[handle.index].get_font_texture_id(font_size);
}

Mesh_Handle generate_text_mesh( Text* text, Font_Settings* font_settings )
{
    Mesh* mesh = new Mesh;
    Font* font = &Font_Manager::loaded_fonts[font_settings->font_handle.index];

    std::vector<float>* vertices = new std::vector<float>();
    std::vector<uint32_t>* indices = new std::vector<uint32_t>();
    std::vector<float>* textures = new std::vector<float>();
    std::vector<float>* norm = new std::vector<float>();

    vertices->clear();
    indices->clear();
    textures->clear();

    int idc_offset = 0;

    float text_x = 0;
    float text_y = 0;

    //int text_idx = 0;

    float x2 = 0;
    float y2 = 0;
    float w = 0;
    float h = 0;
    uint16_t text_width = 0;
    uint16_t text_height = 0;

    uint16_t max_height = 0;
    uint16_t size = font_settings->size;

    for ( u32 i = 0; i < text->size(); i++ ) {
         if ( text->at(i) == '\n' ) {
            text_y -= font_settings->size + font_settings->string_new_line_pad;
            text_x = 0;
         }

         float x_offset = font->generate_char_data(text->at(i), size)->offset_x;
         float y_offset = font->generate_char_data(text->at(i), size)->offset_y;

         x2 = text_x + font->generate_char_data(text->at(i), size)->map_left;
         y2 = -text_y - font->generate_char_data(text->at(i), size)->map_top;
         w = font->generate_char_data(text->at(i), size)->map_width;
         h = font->generate_char_data(text->at(i), size)->map_height;
         text_width = font->get_font_width(size);
         text_height = font->get_font_height(size);

         if ( text_height > max_height ){
            max_height = text_height;
         }

         vertices->push_back(x2);
         vertices->push_back(-y2);
         vertices->push_back(0);
         textures->push_back(x_offset);
         textures->push_back(y_offset);

         vertices->push_back(x2 + w);
         vertices->push_back(-y2);
         vertices->push_back(0);
         textures->push_back(x_offset + w / text_width);
         textures->push_back(y_offset);

         vertices->push_back(x2);
         vertices->push_back(-y2 - h);
         vertices->push_back(0);
         textures->push_back(x_offset);
         textures->push_back(y_offset + h / text_height);

         vertices->push_back(x2 + w);
         vertices->push_back(-y2);
         vertices->push_back(0);
         textures->push_back(x_offset + w / text_width);
         textures->push_back(y_offset);

         vertices->push_back(x2);
         vertices->push_back(-y2 - h);
         vertices->push_back(0);
         textures->push_back(x_offset);
         textures->push_back(y_offset + h / text_height);

         vertices->push_back(x2 + w);
         vertices->push_back(-y2 - h);
         vertices->push_back(0);
         textures->push_back(x_offset + w / text_width);
         textures->push_back(y_offset + h / text_height);

         text_x += font->generate_char_data(text->at(i), size)->advance_x;
         text_y -= font->generate_char_data(text->at(i), size)->advance_y;

         for (int j = 0; j < 6; j++) {
            indices->push_back(idc_offset);
            idc_offset++;
         }
    }

    norm->resize(vertices->size(), 1);

    mesh->indices = indices->data();
    mesh->indices_count = (uint32_t)indices->size();
    mesh->vertices = vertices->data();
    mesh->vertices_count = (uint32_t)vertices->size();
    mesh->textures = textures->data();
    mesh->textures_count = (uint32_t)textures->size();
    mesh->normals = norm->data();
    mesh->normals_count = (uint32_t)norm->size();

    Mesh_Handle handle = load_to_graphics_api(mesh);

    //LOG("HEREEEEEE");

    return handle;
}

} // end namespace Engine

