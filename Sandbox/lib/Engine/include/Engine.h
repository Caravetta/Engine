#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <stdint.h>
#include <string>
#include <unordered_map>
#include <vector>

#include <Engine_Assets.h>
#include <Engine_Types.h>

namespace Engine {

/****************************************/
/*                                      */
/*         Basic Engine Calls           */
/*                                      */
/****************************************/

typedef struct {
    uint16_t    window_width;
    uint16_t    window_height;
    std::string window_title;
} engine_config_t;

ENGINE_API Rc_t init( engine_config_t* engine_config );
ENGINE_API void run();
ENGINE_API void shutdown();
ENGINE_API void set_active_camera( Camera* camera );
ENGINE_API float get_delta_time();

/****************************************/
/*                                      */
/*         Asset Engine Calls           */
/*                                      */
/****************************************/

ENGINE_API Rc_t register_asset( std::string asset_name, std::string file_path, Asset* asset );
ENGINE_API Asset* get_asset( Asset_Handle handle );
ENGINE_API Rc_t get_asset_handle( std::string asset_name, Asset_Handle* handle );

template<typename T>
Rc_t register_asset( std::string asset_name, std::string file_path )
{
    //TODO(JOSH): need to check if that name has already been used for another asset
	return register_asset(asset_name, file_path, new T);
}

template<typename T>
T* get_asset_with_handle( Asset_Handle asset_handle )
{
    return (T*)get_asset(asset_handle);
}

template<typename T>
T* get_asset_by_name( std::string asset_name )
{
    Asset_Handle asset_handle;
    Rc_t rc = get_asset_handle(asset_name, &asset_handle);
    if ( rc == ENGINE_ERROR ) {
        return NULL;
    }

    return get_asset_with_handle<T>(asset_handle);
}

/****************************************/
/*                                      */
/*         Entity Engine Calls          */
/*                                      */
/****************************************/

ENGINE_API Entity create_entity( std::string archetype_name );
ENGINE_API Rc_t delete_entity( Entity entity );
ENGINE_API bool is_valid_entity( Entity entity );

/****************************************/
/*                                      */
/*      Component Engine Calls          */
/*                                      */
/****************************************/

ENGINE_API uint32_t get_max_components();
ENGINE_API uint64_t get_component_size( uint32_t component_id );
ENGINE_API void register_component_info( uint32_t component_id, component_info comp_info );
ENGINE_API uint8_t* get_component_data( Entity entity, uint32_t component_id );

template<typename T>
void register_component( void )
{
    component_info temp_comp;
    temp_comp.create_function = component_create<T>;
    temp_comp.copy_function = component_copy<T>;
    temp_comp.size = sizeof(T);

    if ( typeid(T) == typeid(Transform) ) {
        type_idx_info<T>::id = TRANSFORM_COMP;
    } else if ( typeid(T) == typeid(Mesh_Handle) ) {
        type_idx_info<T>::id = MESH_HANDLE_COMP;
    } else if ( typeid(T) == typeid(Shader_ID) ) {
        type_idx_info<T>::id = SHADER_ID_COMP;
    } else if ( typeid(T) == typeid(Text) ) {
        type_idx_info<T>::id = TEXT_COMP;
    } else if ( typeid(T) == typeid(Font_Settings) ) {
        type_idx_info<T>::id = FONT_SETTINGS_COMP;
    } else if ( typeid(T) == typeid(Texture) ) {
        type_idx_info<T>::id = TEXTURE_COMP;
    } else {
        type_idx_info<T>::id = get_max_components();
    }

    std::cout << "COMPONENT ID REG: " << type_idx_info<T>::id << std::endl;

    register_component_info(type_idx_info<T>::id, temp_comp);
}

template<typename T>
Rc_t add_component( Entity entity )
{
    //TODO(JOSH): need to implement.
    return NOT_IMPLEMENTED;
}

template<typename T>
Rc_t remove_component( Entity entity )
{
    //TODO(JOSH): need to implement.
    return NOT_IMPLEMENTED;
}

template<typename T>
T* get_component( Entity entity )
{
	return (T*)get_component_data(entity, component_id<T>());
}

template<typename T>
bool is_component_set( Entity entity )
{
	//TODO(JOSH): need to implement.
    return false;
}

/****************************************/
/*                                      */
/*         Event Engine Calls           */
/*                                      */
/****************************************/

ENGINE_API Rc_t create_event( std::string event_name );
ENGINE_API Rc_t subscribe_to_event( std::string event_name, void (*callback)(void*, size_t) );
//ENGINE_API Rc_t unsubscribe_to_event(); //TODO(JOSH): need to implement
ENGINE_API Rc_t broadcast_event( std::string event_name, void* data, size_t data_size );

/****************************************/
/*                                      */
/*        System Engine Calls           */
/*                                      */
/****************************************/

void ENGINE_API register_generic_system( System* system );

template<typename T>
void register_system( void )
{
    register_generic_system( new T );
}

/****************************************/
/*                                      */
/*      Archetype Engine Calls          */
/*                                      */
/****************************************/

ENGINE_API Rc_t register_archetype( Archetype archetype, std::string archetype_name );

/****************************************/
/*                                      */
/*         Mesh Engine Calls            */
/*                                      */
/****************************************/

ENGINE_API Mesh_Handle load_to_graphics_api( Mesh* mesh );
ENGINE_API Rc_t deload_from_graphics_api( Mesh_Handle handle );

/****************************************/
/*                                      */
/*         Shader Engine Calls          */
/*                                      */
/****************************************/

ENGINE_API void create_shader_program( unsigned int vertex_id, unsigned int fragment_id, unsigned int* program_id );

/****************************************/
/*                                      */
/*          Font Engine Calls           */
/*                                      */
/****************************************/

ENGINE_API uint32_t get_font_texture_id( Font_Handle handle, uint16_t font_size );
ENGINE_API Mesh_Handle generate_text_mesh( Text* text, Font_Settings* font_settings );

} // end namespace Engine


#endif //__ENGINE_H__

