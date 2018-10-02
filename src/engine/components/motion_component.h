#ifndef __MOTION_COMPONENT_H__
#define __MOTION_COMPONENT_H__

#include "../core/core.h"

COMPONENT(
          Motion_Component,                                         //name of component
          core::Vector3f velocity = core::Vector3f(0.0f, 0.0f, 0.0f);     //start of component data
          core::Vector3f acceleration = core::Vector3f(0.0f, 0.0f, 0.0f);
         )

#endif //__MOTION_COMPONENT_H__
