#if !defined(SHADER_COMPONENT_H)

#include "../core/core.h"

class Shader_Component : public core::Component {
public:
    unsigned int vertex_id;
    unsigned int fragment_id;
    unsigned int program_id;

    Shader_Component();

};

#define SHADER_COMPONENT_H
#endif
