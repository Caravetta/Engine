#if !defined(TEXT_H)

#include <string>
#include "../core_common.h"

namespace core {

    class Text {
    public:
        std::vector<Vector3f> vertices;
        std::vector<Vector2f> textures;

        Text( std::string text );
        Text( std::string text, uint16_t line_length );
    };

} // end namespace core

#define TEXT_H
#endif
