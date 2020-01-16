#include "cube.h"

void load_cube_mesh( Editor_Context& context )
{
     float cube_verts[] = {
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
          -1.0, -1.0,  -1.0,
          1.0, -1.0,  -1.0,
          1.0, 1.0,  -1.0,
          -1.0, 1.0,  -1.0,
          -1.0, -1.0,  1.0,
          1.0, -1.0,  1.0,
          1.0, 1.0,  1.0,
          -1.0, 1.0,  1.0,
     };

     int32_t cube_indices[] = {
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
     //mesh_data.normals.resize(sizeof(cube_norms) / sizeof(float ));
     //memcpy(mesh_data.normals.data(), cube_norms, sizeof(cube_norms));
     mesh_data.indices.resize(sizeof(cube_indices) / sizeof(int32_t));
     memcpy(mesh_data.indices.data(), cube_indices, sizeof(cube_indices));

     Engine::load_mesh(Engine::STATIC_MESH, "Default_Cube", mesh_data);
     Engine::Mesh_Handle mesh_handle = Engine::mesh_handle("Default_Cube");

     context.mesh_map.insert({"Default_Cube", mesh_handle});
}

