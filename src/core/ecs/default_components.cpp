#include "default_components.h"

namespace Engine {

/*
 *   Transform Component
 */

COMPONENT_DEFINE( Transform );
META_INFO_DEFINE( Transform );

void Transform::populate_meta_info_func( Engine::Meta_Info& meta_info )
{
     meta_info.add_field(&Transform::position, "position");
     meta_info.add_field(&Transform::scale, "scale");
     meta_info.add_field(&Transform::rotation, "rotation");
}

} // end namespace Engine

