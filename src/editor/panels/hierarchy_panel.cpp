#include "hierarchy_panel.h"
#include "gui.h"

int init_hierarchy_panel( void )
{
     return 0;
}

void update_hierarchy_panel( Editor_Context& context )
{
	ImGui::SetNextWindowPos(ImVec2(context.panels.hierarchy.x_position,
						      context.panels.hierarchy.y_position));
     ImGui::SetNextWindowSize(ImVec2(context.panels.hierarchy.width,
						       context.panels.hierarchy.height));
     ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
     ImGui::BeginTabBar("Tabs");
     if ( ImGui::BeginTabItem("Hierarchy") == true ) {
          std::vector<std::string> entities = context.entity_manager.get_entity_name_list();
          for ( size_t ii = 0; ii < entities.size(); ii++ ) {
               if ( ImGui::Selectable(entities[ii].c_str(), (ii == context.selected_entity ? true : false) ) == true ) {
                    context.selected_entity = ii;
                    context.entity_selected = true;
               }
          }
          ImGui::EndTabItem();
     }
     ImGui::EndTabBar();
     ImGui::End();
}

