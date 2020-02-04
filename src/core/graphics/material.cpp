#include "material.h"

namespace Engine {

COMPONENT_DEFINE( Material );
META_INFO_DEFINE( Material );

void Material::populate_meta_info_func( Engine::Meta_Info& meta_info )
{
     meta_info.add_field(&Material::shader_id, "shader_id");
}

} // end namespace Engine

