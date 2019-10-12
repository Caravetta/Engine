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
     META_STRUCT_DECLARE( Transform );
     static void populate_meta_struct_func( Engine::Meta_Struct& meta_struct );

     Engine::Vector3f position;
     Engine::Vector3f scale;
     Engine::Vector3f rotation;
};


/*
 *   Base Camera Component
 */

struct Base_Camera {
     COMPONENT_DECLARE( Base_Camera );
     META_STRUCT_DECLARE( Base_Camera );
     static void populate_meta_struct_func( Engine::Meta_Struct& meta_struct );

     Engine::Vector3f position;
     Engine::Vector3f rotation;
     Engine::Matrix4f view_matrix;
     Engine::Matrix4f projection_matrix;
};


/*
 *   Basic 3D Camera Component
 */

struct Basic_3D_Camera {
     COMPONENT_DECLARE( Basic_3D_Camera );
     META_STRUCT_DECLARE( Basic_3D_Camera );
     static void populate_meta_struct_func( Engine::Meta_Struct& meta_struct );

     float field_of_view;
     float aspect_ratio;
     float near_plane;
     float far_plane;
};

} // end namespace Engine

#endif //__DEFAULT_COMPONENTS_H__