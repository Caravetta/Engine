#include "light.h"

namespace Engine {

COMPONENT_DEFINE( Light );
META_INFO_DEFINE( Light );

void Light::populate_meta_info_func( Engine::Meta_Info& meta_info )
{
     meta_info.add_field(&Light::color, "color");
}

} // end namespace Engine

