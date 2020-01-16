#include <vector>
#include <unordered_map>
#include "mesh.h"
#include "handle.h"
#include "crc32.h"
#include "platform_graphics.h"

namespace Engine {

#define MESH_HANDLE_BLOCK_SIZE 100

struct Mesh_Asset_Manager {
     std::unordered_map<uint32_t, uint32_t> mesh_map;
     Handle_Manager handle_manager;
     std::vector<Mesh_Data> mesh_data;
     std::vector<Mesh> meshes;
     std::vector<uint32_t> vertex_ids;
};

Mesh_Asset_Manager* mesh_manager = NULL;

void _update_data_vecs( size_t num_handles );

Rc_t init_mesh_asset_manager( void )
{
     Rc_t rc = SUCCESS;

     if ( mesh_manager == NULL ) {
          mesh_manager = new (std::nothrow) Mesh_Asset_Manager;
          if ( mesh_manager != NULL ) {

               mesh_manager->handle_manager.set_block_size(MESH_HANDLE_BLOCK_SIZE);
               size_t num_handles = mesh_manager->handle_manager.num_handles();
               _update_data_vecs(num_handles);
          } else {
               rc = MEMORY_ALLOC_FAILED;
          }
     }

     return rc;
}

#if 0
Rc_t load_mesh( Mesh_Type type, std::string file )
{
     return SUCCESS;
}
#endif

Rc_t load_mesh( Mesh_Type type, std::string mesh_name, Mesh_Data& mesh_data )
{
     mesh_manager->mesh_data.push_back(mesh_data);

     size_t data_idx = mesh_manager->mesh_data.size() - 1;
     Handle handle = mesh_manager->handle_manager.get_handle();
     uint32_t idx = handle_index(handle);
     Mesh& mesh = mesh_manager->meshes[idx];

     mesh.data = &mesh_manager->mesh_data[data_idx];
     mesh.handle = handle;
     mesh.indices_offset = 0;
     mesh.indices_count = mesh.data->indices.size();
     mesh.mesh_name = mesh_name;

     // load data into graphics card
     if ( type == Mesh_Type::STATIC_MESH ) {
          mesh.vertex_array_id = create_vertex_array();
          bind_vertex_array(mesh.vertex_array_id);

          size_t num_indices = mesh.data->indices.size();
          LOG("JOSH num_indices %zu", num_indices);
          if ( num_indices != 0 ) {
               mesh.indice_buffer_id = create_vertex_buffer();
               bind_vertex_buffer(Buffer_Type::ELEMENT_ARRAY_BUFFER, mesh.indice_buffer_id);
               buffer_vertex_data(Buffer_Type::ELEMENT_ARRAY_BUFFER, (uint8_t*)mesh.data->indices.data(), sizeof(uint32_t) * num_indices, STATIC_DRAW);
               bind_vertex_buffer(Buffer_Type::ELEMENT_ARRAY_BUFFER, 0);
          }

          size_t num_positions = mesh.data->positions.size();
          LOG("JOSH num_positions %zu", num_positions);
          if ( num_positions != 0 ) {
               mesh.vertex_buffer_id = create_vertex_buffer();
               bind_vertex_buffer(Buffer_Type::ARRAY_BUFFER, mesh.vertex_buffer_id);
               buffer_vertex_data(Buffer_Type::ARRAY_BUFFER, (uint8_t*)mesh.data->positions.data(), sizeof(float) * num_positions, STATIC_DRAW);
               enable_vertex_attrib(POSITION_ID);
               define_vertex_attrib(POSITION_ID, 3, false, Engine::FLOAT_DATA, 3 * sizeof(float), 0);
               bind_vertex_buffer(Buffer_Type::ARRAY_BUFFER, 0);
          } else {
               LOG_ERROR("There is no postion data");
               //TODO(JOSH): need to clean up vertex array
               return ENGINE_ERROR;
          }

          //load normals
          size_t num_normals = mesh.data->normals.size();
          if ( num_normals != 0 ) {
               LOG("JOSH HERE");
               mesh.vertex_buffer_id = create_vertex_buffer();
               bind_vertex_buffer(Buffer_Type::ARRAY_BUFFER, mesh.vertex_buffer_id);
               buffer_vertex_data(Buffer_Type::ARRAY_BUFFER, (uint8_t*)mesh.data->normals.data(), sizeof(float) * num_normals, STATIC_DRAW);
               enable_vertex_attrib(NORMAL_ID);
               define_vertex_attrib(NORMAL_ID, 3, false, Engine::FLOAT_DATA, 3 * sizeof(float), 0);
               bind_vertex_buffer(Buffer_Type::ARRAY_BUFFER, 0);
          }

          bind_vertex_array(0);
     } else if ( type == Mesh_Type::DYNAMIC_MESH ) {
          //TODO(JOSH): need to implement
     } else {
          LOG_ERROR("Unknown type of mesh");
          return ENGINE_ERROR;
     }

     uint32_t string_crc = crc32(mesh_name.c_str());
     mesh_manager->mesh_map.insert({string_crc, idx});

     return SUCCESS;
}

Mesh_Handle mesh_handle( std::string mesh_name )
{
     uint32_t string_crc = crc32(mesh_name.c_str());
     std::unordered_map<uint32_t, uint32_t>::const_iterator iter = mesh_manager->mesh_map.find(string_crc);
     if ( iter == mesh_manager->mesh_map.end() ) {
          return INVALID_MESH_HANDLE;
     }

     Mesh& mesh = mesh_manager->meshes[iter->second];

     return mesh.handle;
}

Mesh_Render_Info mesh_render_info( Mesh_Handle mesh_handle )
{
     if ( mesh_manager->handle_manager.valid_handle(mesh_handle) ) {
          //return
     } else {
          Mesh_Render_Info render_info = {0};
          return render_info;
     }

     Mesh_Render_Info render_info = {0};
     return render_info;
}

COMPONENT_DEFINE( Mesh_Info );
META_INFO_DEFINE( Mesh_Info );

void Mesh_Info::populate_meta_info_func( Engine::Meta_Info& meta_info )
{
     meta_info.add_field(&Mesh_Info::handle, "handle");
}

void _update_data_vecs( size_t num_handles )
{
     //mesh_manager->mesh_data.resize(num_handles);
     mesh_manager->meshes.resize(num_handles);
     mesh_manager->vertex_ids.resize(num_handles);
}

Rc_t  bind_mesh( const Mesh_Handle& mesh_handle, size_t& ind )
{
     Rc_t rc = SUCCESS;

     if ( mesh_manager->handle_manager.valid_handle(mesh_handle) ) {
          uint32_t idx = handle_index(mesh_handle);
          Mesh& mesh = mesh_manager->meshes[idx];
          size_t num_indices = mesh.indices_count;

          if ( num_indices > 0 ) {
               ind = num_indices;
               bind_vertex_array(mesh.vertex_array_id);
               bind_vertex_buffer(Buffer_Type::ELEMENT_ARRAY_BUFFER, mesh.indice_buffer_id);
          } else {
               //TODO(JOSH): need to support non indices
          }
     } else {
          rc = ENGINE_ERROR;
     }

     return rc;
}

} // end namespace Engine

