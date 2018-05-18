#if !defined(POSITION_COMPONENT_H)

#include "../core/core.h"

class Position_Component : public core::Component {
public:
    core::Vector3f position;

    Position_Component();

};

#define POSITION_COMPONENT_H
#endif
