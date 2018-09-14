#if !defined(SHADER_COMPONENT_H)

#include "../core/core.h"

COMPONENT(
          // Name of Component
          Shader_Component,

          // Start of Component Data
          uint32_t vertex_id;
          uint32_t fragment_id;
          uint32_t program_id;
         )

#define SHADER_COMPONENT_H
#endif
