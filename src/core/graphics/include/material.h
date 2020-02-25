#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "core_common.h"
#include "shader.h"
#include "component.h"
#include "reflection.h"


namespace Engine {

ENGINE_STRUCT()
struct Material {
     COMPONENT_DECLARE( Material );
     META_INFO_DECLARE( Material );

     ENGINE_COMPONENT()

     static void populate_meta_info_func( Engine::Meta_Info& meta_info );

     int32_t shader_id;
};

} // end namespace Engine

#endif //__MATERIAL_H__
