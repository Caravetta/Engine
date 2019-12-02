#include "cube.h"

void load_cube_mesh( Editor_Context& context )
{
     float cube_verts[] = {
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
     };

     int32_t cube_indices[] = {
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

