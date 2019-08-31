#ifndef __MESH_H__
#define __MESH_H__

#include <vector>
#include "core_common.h"
#include "vector3f.h"
#include "vector2f.h"
#include "reflection.h"

namespace Engine {

//TODO(JOSH): add to reflection system

class Mesh_Data {
public:
     std::vector<Vector3f> __positions;
     std::vector<Vector3f> __normals;
     std::vector<Vector2f> __text_cords;

     Mesh_Data( void );

     std::vector<Vector3f>& positions( void ) { return __positions; };
     std::vector<Vector3f>& normals( void ) { return __normals; };
     std::vector<Vector2f>& text_cords( void ) { return __text_cords; };
};

class Mesh {
public:
     Mesh_Data& mesh_data;

};

} // end namespace Engine

#endif //__MESH_H__
