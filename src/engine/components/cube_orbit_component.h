#if !defined(CUBE_ORBIT_COMPONENT_H)

#include "../core/core.h"

COMPONENT(
          Cube_Orbit_Component,
          float speed = 1;
          float width = 4;
          float height = 4;
          float time_diff = 0;
          core::Vector3f start_pos;
          bool start_set = false;
         )

#define CUBE_ORBIT_COMPONENT_H
#endif
