#if !defined(POSITION_COMPONENT_H)

#include "../core/core.h"

COMPONENT(
          Position_Component,       //name of component
          core::Vector3f position;  //start of component data
          std::string test_string = "awdawd";
         )

#define POSITION_COMPONENT_H
#endif
