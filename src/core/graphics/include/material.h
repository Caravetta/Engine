#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "core_common.h"
#include "shader.h"
#include "component.h"
#include "reflection.h"


namespace Engine {

#if 0
class Material {
private:
     Shader* __shader;

public:
     Material( Shader& shader );
     ~Material( void );
     Shader& shader( void );
};
#endif

struct Material {
     COMPONENT_DECLARE( Material );
     META_INFO_DECLARE( Material );

     static void populate_meta_info_func( Engine::Meta_Info& meta_info );

     int32_t shader_id;
};

} // end namespace Engine

#endif //__MATERIAL_H__
