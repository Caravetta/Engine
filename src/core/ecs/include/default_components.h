#ifndef __DEFAULT_COMPONENTS_H__
#define __DEFAULT_COMPONENTS_H__

#include "component.h"
#include "engine_math.h"
#include "reflection.h"

namespace Engine {

/*
 *   Transform Component
 */

struct Transform {
     COMPONENT_DECLARE( Transform );
     META_INFO_DECLARE( Transform );

     static void populate_meta_info_func( Engine::Meta_Info& meta_info );

     Engine::Vector3f position;
     Engine::Vector3f scale;
     Engine::Vector3f rotation;
};

} // end namespace Engine

#endif //__DEFAULT_COMPONENTS_H__
