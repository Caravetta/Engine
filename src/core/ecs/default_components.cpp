#include "default_components.h"

namespace Engine {

/*
 *   Transform Component
 */

COMPONENT_DEFINE( Transform );
META_STRUCT_DEFINE( Transform );

void Transform::populate_meta_struct_func( Engine::Meta_Struct& meta_struct )
{
     meta_struct.add_field(&Transform::position,  "position");
     meta_struct.add_field(&Transform::scale,     "scale");
     meta_struct.add_field(&Transform::rotation,  "rotation");
}


/*
 *   Base Camera Component
 */

COMPONENT_DEFINE( Base_Camera );
META_STRUCT_DEFINE( Base_Camera );

void Base_Camera::populate_meta_struct_func( Engine::Meta_Struct& meta_struct )
{
     meta_struct.add_field(&Base_Camera::position,          "position");
     meta_struct.add_field(&Base_Camera::rotation,          "rotation");
     meta_struct.add_field(&Base_Camera::view_matrix,       "view_matrix");
     meta_struct.add_field(&Base_Camera::projection_matrix, "projection_matrix");
}


/*
 *   Basic 3D Camera Component
 */

COMPONENT_DEFINE( Basic_3D_Camera );
META_STRUCT_DEFINE( Basic_3D_Camera );

void Basic_3D_Camera::populate_meta_struct_func( Engine::Meta_Struct& meta_struct )
{
     meta_struct.add_field(&Basic_3D_Camera::field_of_view, "field_of_view");
     meta_struct.add_field(&Basic_3D_Camera::aspect_ratio,  "aspect_ratio");
     meta_struct.add_field(&Basic_3D_Camera::near_plane,    "near_plane");
     meta_struct.add_field(&Basic_3D_Camera::far_plane,     "far_plane");
}

} // end namespace Engine

