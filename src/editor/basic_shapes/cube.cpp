#include "cube.h"

void load_cube_mesh( Editor_Context& context )
{
     float cube_verts[] = {
     #if 0
          // front
          -1.0, -1.0,  1.0,
          1.0, -1.0,  1.0,
          1.0,  1.0,  1.0,
          -1.0,  1.0,  1.0,
          // back
          -1.0, -1.0, -1.0,
          1.0, -1.0, -1.0,
          1.0,  1.0, -1.0,
          -1.0,  1.0, -1.0
     #endif
          -1.0, -1.0,  -1.0,
          1.0, -1.0,  -1.0,
          1.0, 1.0,  -1.0,
          -1.0, 1.0,  -1.0,
          -1.0, -1.0,  1.0,
          1.0, -1.0,  1.0,
          1.0, 1.0,  1.0,
          -1.0, 1.0,  1.0,
     };

     float cube_norms[] = {
          0, -1.0, 0,
          0, 1.0, 0,
          1.0, 0, 0,
          0, 0, 1.0,
          -1.0, 0, 0,
          0, 0, -1.0,
          1.0, 0, 0,
     };

     int32_t cube_indices[] = {
          #if 0
          // front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
          #endif
          0, 1, 3, 3, 1, 2,
          1, 5, 2, 2, 5, 6,
          5, 4, 6, 6, 4, 7,
          4, 0, 7, 7, 0, 3,
          3, 2, 7, 7, 2, 6,
          4, 5, 0, 0, 5, 1
     };

     Engine::Mesh_Data mesh_data;
     mesh_data.positions.resize(sizeof(cube_verts) / sizeof(float ));
     memcpy(mesh_data.positions.data(), cube_verts, sizeof(cube_verts));
     mesh_data.indices.resize(sizeof(cube_indices) / sizeof(int32_t));
     memcpy(mesh_data.indices.data(), cube_indices, sizeof(cube_indices));

     Engine::load_mesh(Engine::STATIC_MESH, "Default_Cube", mesh_data);
     Engine::Mesh_Handle mesh_handle = Engine::mesh_handle("Default_Cube");

     context.mesh_map.insert({"Default_Cube", mesh_handle});
}

