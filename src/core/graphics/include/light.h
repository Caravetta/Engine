#ifndef __LIGHT_H__
#define __LIGHT_H__

#include "component.h"
#include "engine_math.h"
#include "reflection.h"

namespace Engine {

struct Light {
     COMPONENT_DECLARE( Light );
     META_INFO_DECLARE( Light );

     static void populate_meta_info_func( Engine::Meta_Info& meta_info );

     Color color;
};

} // end namespace Engine

#endif //__LIGHT_H__
