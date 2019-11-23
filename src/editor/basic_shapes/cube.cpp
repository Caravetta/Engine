#include "cube.h"

struct Cube_Data {
     uint32_t vert_array_id;
     uint32_t indices_buf;
     uint32_t vert_buf;
};

Cube_Data* cube_data = NULL;


void load_cube_mesh( void )
{
     if ( cube_data != NULL ) {
          return;
     }

     cube_data = new (std::nothrow) Cube_Data;
     if ( cube_data == NULL ) {
          //TODO(JOSH): need to hanle the error here
          return;
     }

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

     float cube_indices[] = {
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

     cube_data->vert_array_id = Engine::create_vertex_array();
     Engine::bind_vertex_array(cube_data->vert_array_id);

     cube_data->indices_buf = Engine::create_vertex_buffer();
     Engine::bind_vertex_buffer(Engine::Buffer_Type::ELEMENT_ARRAY_BUFFER, cube_data->indices_buf);
     Engine::buffer_vertex_data(Engine::Buffer_Type::ELEMENT_ARRAY_BUFFER,
                               (uint8_t*)cube_indices, sizeof(cube_indices), Engine::STATIC_DRAW);
     Engine::bind_vertex_buffer(Engine::Buffer_Type::ELEMENT_ARRAY_BUFFER, 0);

     cube_data->vert_buf = Engine::create_vertex_buffer();
     Engine::bind_vertex_buffer(Engine::Buffer_Type::ARRAY_BUFFER, cube_data->vert_buf);
     Engine::buffer_vertex_data(Engine::Buffer_Type::ARRAY_BUFFER, (uint8_t*)cube_verts, sizeof(cube_verts), Engine::STATIC_DRAW);
     Engine::enable_vertex_attrib(0);
     Engine::define_vertex_attrib(0, 3, false, Engine::FLOAT_DATA, 3 * sizeof(float), 0);
     Engine::bind_vertex_buffer(Engine::Buffer_Type::ARRAY_BUFFER, 0);

     Engine::bind_vertex_array(0);
}

Engine::Mesh_Handle get_cube_mesh( void )
{
     return 0;
}

