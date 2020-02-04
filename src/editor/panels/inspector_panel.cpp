#include "inspector_panel.h"
#include "gui.h"

static bool _add_component;
static char _ent_buffer[50];

int init_inspector_panel( void )
{
	_add_component = false;

     return 0;
}

void update_inspector_panel( Editor_Context& context )
{
	ImGui::SetNextWindowPos(ImVec2(context.panels.instector.x_position,
							 context.panels.instector.y_position));
     ImGui::SetNextWindowSize(ImVec2(context.panels.instector.width,
						       context.panels.instector.height));
     ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
     ImGui::BeginTabBar("Tabs");
     if ( ImGui::BeginTabItem("Inspector") == true ) {
          if ( context.entity_selected ) {
               Engine::Entity selected_ent = context.entity_manager.get_entity(context.selected_entity);
               //ImGui::Indent((instector_tab_width / 2) - button_width);
               if ( ImGui::Button("Add Component", ImVec2(context.panels.instector.width, 0)) ) {
                    _add_component = true;
               }

               if ( _add_component ) {
                    ImGui::SetNextWindowSize(ImVec2(context.panels.instector.width - 12.0f, 300.0f));
                    ImGui::SetNextWindowPos(ImVec2((context.window_width - context.panels.instector.width + 8.0f), 70.0f));
                    ImGui::Begin("End", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
                    for ( size_t kk = 0; kk < context.component_list.size(); kk++ ) {
                         if ( ImGui::Selectable(Engine::get_component_name(context.component_list[kk]), false ) == true ) {
                              _add_component = false;
                              Engine::add_component(selected_ent, context.component_list[kk]);
                         }
                    }
                    if (  !ImGui::IsWindowFocused() ) {
                    	_add_component = false;
                    }
                    ImGui::End();

               }

               ImGui::Separator();
			std::string* entity_name = context.entity_manager.entity_name(context.selected_entity);
               memset(_ent_buffer, 0, sizeof(_ent_buffer));
               memcpy(_ent_buffer, entity_name->c_str(), entity_name->size());
               if ( ImGui::InputText( "Entity Name", _ent_buffer, 50, ImGuiInputTextFlags_AutoSelectAll | ImGuiInputTextFlags_EnterReturnsTrue ) ) {
                    context.entity_manager.update_entity_name(context.selected_entity, _ent_buffer);
               }

               if ( ImGui::IsItemDeactivatedAfterEdit() ) {
                    context.entity_manager.update_entity_name(context.selected_entity, _ent_buffer);
               }

               std::vector<Engine::Component_ID> ent_comps = Engine::entity_components(selected_ent);
               ImGui::NewLine();
               for ( size_t kk = 0; kk < ent_comps.size(); kk++ ) {
                    const char* comp_name = Engine::get_component_name(ent_comps[kk]);
                    if ( ImGui::CollapsingHeader(comp_name, ImGuiTreeNodeFlags_DefaultOpen) ) {
                         Engine::Meta_Info* meta_info = Engine::Reflection::get_meta_info(comp_name);

                         if ( meta_info != NULL ) {
                              uint8_t* comp_data = Engine::get_component_data(selected_ent, ent_comps[kk]);

                              for ( size_t ll = 0; ll < meta_info->__fields.size(); ll++ ) {
                                   switch ( meta_info->__fields[ll].type ) {
                                   case Engine::META_TYPE_VECTOR3F: {
                                        ImGui::InputFloat3(meta_info->__fields[ll].__name, (float*)comp_data);
                                   } break;
                                   case Engine::META_TYPE_FLOAT: {
                                        ImGui::InputFloat(meta_info->__fields[ll].__name, (float*)comp_data);
                                   } break;
                                   case Engine::META_TYPE_U64: {
                                        ImGui::InputScalar(meta_info->__fields[ll].__name, ImGuiDataType_U64, (void*)comp_data);
                                   } break;
                                   case Engine::META_TYPE_U32: {
                                        ImGui::InputScalar(meta_info->__fields[ll].__name, ImGuiDataType_U32, (void*)comp_data);
                                   } break;
                                   default: {
                                   } break;
                                   }

							comp_data = comp_data + meta_info->__fields[ll].__size;
                              }
                         }
                         ImGui::NewLine();
                         ImGui::Separator();
                    }
               }

          }
          ImGui::EndTabItem();
     }
     ImGui::EndTabBar();
     ImGui::End();
}

