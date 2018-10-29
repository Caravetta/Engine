#ifndef __STATIC_TEXT_COMPONENT_H__
#define __STATIC_TEXT_COMPONENT_H__

#include <vector>
#include <string>
#include "../core/core.h"

COMPONENT(
          // Name of Component
          Static_Text_Component,

          // Start of Component Data
          std::string text;
          uint16_t size;
          std::vector<float>* vertices;
          std::vector<uint32_t>* indices;
          std::vector<float>* textures;
          core::vao_t* vao;

          // Start of Helper Functions
          void generate_static_text( std::string user_text, uint16_t font_size, core::Font* font, uint16_t new_line_pad );
         )

#endif //__STATIC_TEXT_COMPONENT_H__
