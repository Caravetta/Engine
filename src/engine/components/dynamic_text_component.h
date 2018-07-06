#if !defined(DYNAMIC_TEXT_COMPONENT_H)

#include <vector>
#include <string>
#include "../core/core.h"

class Dynamic_Text_Component : public core::Component {
public:
    std::string text;
    uint16_t size;
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    std::vector<float> textures;
    core::vao* vao;
    core::Font* text_font;

    Dynamic_Text_Component();
    void generate_dynamic_text( std::string user_text, uint16_t font_size, core::Font* font );
    void regenerate_text();
};

#define DYNAMIC_TEXT_COMPONENT_H
#endif
