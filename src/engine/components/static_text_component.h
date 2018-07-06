#if !defined(STATIC_TEXT_COMPONENT_H)

#include <vector>
#include <string>
#include "../core/core.h"

class Static_Text_Component : public core::Component {
public:
    std::string text;
    uint16_t size;
    std::vector<float> vertices;
    std::vector<uint32_t> indices;
    std::vector<float> textures;
    core::vao* vao;

    Static_Text_Component();
    void generate_static_text( std::string user_text, uint16_t font_size, core::Font* font, uint16_t new_line_pad );
};

#define STATIC_TEXT_COMPONENT_H
#endif
