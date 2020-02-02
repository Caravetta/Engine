#ifndef __EDITOR_CONTEXT_H__
#define __EDITOR_CONTEXT_H__

#include <string>
#include <unordered_map>
#include "engine_core.h"
#include "entity_manager.h"
#include "mesh_loader.h"

struct Panel_Settings {
     float width;
     float height;
     float x_position;
     float y_position;
};

struct Panels {
     Panel_Settings menu_bar;
     Panel_Settings console;
     Panel_Settings instector;
     Panel_Settings hierarchy;
     Panel_Settings scene;
};

struct Editor_Context {
public:
     Engine::Window*                                        window;
     float                                                  window_width;
     float                                                  window_height;
     Entity_Manager                                         entity_manager;
     bool                                                   entity_selected;
     size_t                                                 selected_entity;
     std::vector<Engine::Component_ID>                      component_list;
     Panels                                                 panels;
     Engine::Texture_Handle                                 scene_texture;
     std::unordered_map<std::string, Engine::Mesh_Handle>   mesh_map;
     std::unordered_map<std::string, int32_t>               shader_map;
     Mesh_Loader*                                           mesh_loader;
     Engine::Camera*                                        scene_camera;

     static Editor_Context* get_instance( void );

private:
     Editor_Context( void );
     static Editor_Context* instance;
};

#endif //__EDITOR_CONTEXT_H__
