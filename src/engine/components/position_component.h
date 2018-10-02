#ifndef __POSITION_COMPONENT_H__
#define __POSITION_COMPONENT_H__

#include "../core/core.h"

COMPONENT(
          Position_Component,       //name of component
          core::Vector3f position;  //start of component data
          std::string test_string = "awdawd";
         )

#endif //__POSITION_COMPONENT_H__
