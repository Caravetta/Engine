#if !defined(TEXTURE_COMPONENT_H)

#include "../core/core.h"

class Texture_Component : public core::Component {
public:
    uint32_t texture_id;

    Texture_Component();
};

#define TEXTURE_COMPONENT_H
#endif
