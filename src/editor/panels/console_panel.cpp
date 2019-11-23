#include "console_panel.h"
#include "gui.h"

int init_console_panel( void )
{
	return 0;
}

void update_console_panel( Editor_Context& context )
{
	ImGui::SetNextWindowPos(ImVec2(context.panels.console.x_position,
							 context.panels.console.y_position));
     ImGui::SetNextWindowSize(ImVec2(context.panels.console.width,
						       context.panels.console.height));
     ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
     ImGui::BeginTabBar("Tabs");
     if ( ImGui::BeginTabItem("Assets") == true ) {
          ImGui::SetNextWindowSize(ImVec2((context.window_width * 0.1f), (context.panels.console.height - 27.0f)));
          ImGui::SetNextWindowPos(ImVec2(0.0f, (context.window_height - context.panels.console.height + 27)));
          ImGui::Begin("Asset List", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
          if ( ImGui::CollapsingHeader("Assets", ImGuiTreeNodeFlags_DefaultOpen) ) {

          }
          ImGui::End();
          ImGui::EndTabItem();
     }
     if ( ImGui::BeginTabItem("Console") == true ) {
          ImGui::EndTabItem();
     }
     if ( ImGui::BeginTabItem("Performace") == true ) {
          ImGui::EndTabItem();
     }
     ImGui::EndTabBar();
     ImGui::End();
}

