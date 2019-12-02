#include "menu_bar_panel.h"
#include "gui.h"

int init_menu_bar_panel( void )
{
     return 0;
}

void update_menu_bar_panel( Editor_Context& context )
{
     ImGui::SetNextWindowBgAlpha(1);
     ImGui::SetNextWindowPos(ImVec2(context.panels.menu_bar.x_position,
                                    context.panels.menu_bar.y_position));
     ImGui::SetNextWindowSize(ImVec2(context.panels.menu_bar.width,
                                     context.panels.menu_bar.height));

     ImGui::Begin("Menu", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar |
                                ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                                ImGuiWindowFlags_NoBackground);

	ImGui::BeginMenuBar();
     if ( ImGui::BeginMenu("File", true) ) {
          ImGui::Spacing();
          if ( ImGui::MenuItem("New Project") == true ) {
               LOG("Create New Project");
          }
          ImGui::Spacing();
          if ( ImGui::MenuItem("Open Project") == true ) {
               LOG("Open Project");
          }
          ImGui::Spacing();
          ImGui::Spacing();
          ImGui::Separator();
          ImGui::Spacing();

          ImGui::Spacing();
          if ( ImGui::MenuItem("Exit") == true ) {
               //break;
          }
          ImGui::Spacing();
          ImGui::EndMenu();
     }
     if ( ImGui::BeginMenu("Edit", true) ) {
          ImGui::Spacing();
          if ( ImGui::BeginMenu("Test") ) {
               ImGui::Spacing();
               if ( ImGui::MenuItem("Test1") == true ) {
               }
               ImGui::Spacing();
               ImGui::EndMenu();

          }
          ImGui::EndMenu();
     }
     if ( ImGui::BeginMenu("GameObjects", true) ) {
          ImGui::Spacing();
          if ( ImGui::BeginMenu("Create") ) {
               ImGui::Spacing();
               if ( ImGui::MenuItem("Entity") == true ) {
                    context.entity_manager.create_entity();
               }
               if ( ImGui::MenuItem("Cube") == true ) {
                    Engine::Entity entity = context.entity_manager.create_entity();

                    Engine::add_components(entity, {Engine::component_id<Engine::Transform>(),
                                                    Engine::component_id<Engine::Mesh_Info>(),
                                                    Engine::component_id<Engine::Material>()});

                    Engine::Transform* transform = Engine::get_component<Engine::Transform>(entity);
                    transform->position = Engine::Vector3f(0, 0, 0);
                    transform->scale = Engine::Vector3f(1.0f, 1.0f, 1.0f);
                    transform->rotation = Engine::Vector3f(0, 0, 0);

                    Engine::Mesh_Info* mesh_info = Engine::get_component<Engine::Mesh_Info>(entity);
                    mesh_info->handle = context.mesh_map["Default_Cube"];

                    Engine::Material* material_info = Engine::get_component<Engine::Material>(entity);
                    material_info->shader_id = context.shader_map["Default_Shader"];

               }
               ImGui::Spacing();
               ImGui::EndMenu();

          }
          ImGui::Spacing();
          ImGui::EndMenu();
     }
     ImGui::EndMenuBar();
     ImGui::End();
}

