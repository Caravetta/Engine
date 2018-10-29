#include "dynamic_text_component.h"

void Dynamic_Text_Component::generate_dynamic_text( std::string user_text, uint16_t font_size, core::Font* font, uint16_t new_line_pad )
{
    text = user_text;
    size = font_size;

    vertices = new std::vector<float>();
    indices = new std::vector<uint32_t>();
    textures = new std::vector<float>();

    vao = NULL;
    vertices->clear();
    indices->clear();
    textures->clear();

    int idc_offset = 0;

    float text_x = 0;
    float text_y = 0;

    int text_idx = 0;

    float x2 = 0;
    float y2 = 0;
    float w = 0;
    float h = 0;
    uint16_t text_width = 0;
    uint16_t text_height = 0;

    for (int i = 0; i < text.size(); i++) {
         if ( text[i] == '\n' ) {
            text_y -= font_size + new_line_pad;
            text_x = 0;
         }

         float x_offset = font->generate_char_data(text[i], size)->offset_x;
         float y_offset = font->generate_char_data(text[i], size)->offset_y;

         x2 = text_x + font->generate_char_data(text[i], size)->map_left;
         y2 = -text_y - font->generate_char_data(text[i], size)->map_top;
         w = font->generate_char_data(text[i], size)->map_width;
         h = font->generate_char_data(text[i], size)->map_height;
         text_width = font->get_font_width(font_size);
         text_height = font->get_font_height(font_size);

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

         text_x += font->generate_char_data(text[i], size)->advance_x;
         text_y -= font->generate_char_data(text[i], size)->advance_y;

         for (int j = 0; j < 6; j++) {
            indices->push_back(idc_offset);
            idc_offset++;
         }
    }

    vao = new core::vao_t;
    core::create_vao(vao);
    core::bind_vao(vao);
    core::create_index_buffer(vao, (int*)indices->data(), (int)indices->size(), core::DYNAMIC_DRAW);
    core::create_float_attribute(vao, 0, vertices->data(), (int)vertices->size() * sizeof(float), 3, core::DYNAMIC_DRAW);
    core::create_float_attribute(vao, 2, textures->data(), (int)textures->size() * sizeof(float), 2, core::DYNAMIC_DRAW);
    core::unbind_vao();
}

void Dynamic_Text_Component::regenerate_dynamic_text( std::string user_text, uint16_t font_size, core::Font* font, uint16_t new_line_pad )
{
    text = user_text;
    size = font_size;

    vertices->clear();
    indices->clear();
    textures->clear();

    int idc_offset = 0;

    float text_x = 0;
    float text_y = 0;

    int text_idx = 0;

    float x2 = 0;
    float y2 = 0;
    float w = 0;
    float h = 0;
    uint16_t text_width = 0;
    uint16_t text_height = 0;

    for (int i = 0; i < text.size(); i++) {
         if ( text[i] == '\n' ) {
            text_y -= font_size + new_line_pad;
            text_x = 0;
         }

         float x_offset = font->generate_char_data(text[i], size)->offset_x;
         float y_offset = font->generate_char_data(text[i], size)->offset_y;

         x2 = text_x + font->generate_char_data(text[i], size)->map_left;
         y2 = -text_y - font->generate_char_data(text[i], size)->map_top;
         w = font->generate_char_data(text[i], size)->map_width;
         h = font->generate_char_data(text[i], size)->map_height;
         text_width = font->get_font_width(font_size);
         text_height = font->get_font_height(font_size);

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

         text_x += font->generate_char_data(text[i], size)->advance_x;
         text_y -= font->generate_char_data(text[i], size)->advance_y;

         for (int j = 0; j < 6; j++) {
            indices->push_back(idc_offset);
            idc_offset++;
         }
    }

    core::bind_vao(vao);
    core::update_index_buffer(vao, (int*)indices->data(), (int)indices->size(), core::DYNAMIC_DRAW);
    core::update_float_attribute(vao, 0, vertices->data(), (int)vertices->size() * sizeof(float), core::DYNAMIC_DRAW);
    core::update_float_attribute(vao, 2, textures->data(), (int)textures->size() * sizeof(float), core::DYNAMIC_DRAW);
    core::unbind_vao();

}
