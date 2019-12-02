#include "material.h"

namespace Engine {

COMPONENT_DEFINE( Material );
META_INFO_DEFINE( Material );

void Material::populate_meta_info_func( Engine::Meta_Info& meta_info )
{
     meta_info.add_field(&Material::shader_id, "shader_id");
}

#if 0
Material::Material( Shader& shader )
{
     __shader = &shader;
}

Material::~Material( void )
{
     // Do nothing
}

Shader& Material::shader( void )
{
     return *__shader;
}
#endif
} // end namespace Engine

