#if !defined(MESH_COMPONENT_H)

#include "../core/core.h"

class Mesh_Component : public core::Component {
public:
    core::Handle mesh_handle;

    Mesh_Component();
};

#define MESH_COMPONENT_H
#endif
