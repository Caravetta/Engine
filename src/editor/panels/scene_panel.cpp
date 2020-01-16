#include "scene_panel.h"
#include "gui.h"

int init_scene_panel( void )
{
	return 0;
}
static ImGuiEx::Canvas canvas;
auto viewOrigin = canvas.ViewOrigin();
auto viewScale = canvas.ViewScale();
ImVec2 mouse_pos;
void update_scene_panel( Editor_Context& context )
{
	ImGui::SetNextWindowPos(ImVec2(context.panels.scene.x_position,
							 context.panels.scene.y_position));
     ImGui::SetNextWindowSize(ImVec2(context.panels.scene.width,
							  context.panels.scene.height));
     ImGui::Begin("Scene", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
     ImGui::BeginTabBar("Tabs");
     if ( ImGui::BeginTabItem("Scene") == true ) {
          if ( context.scene_texture != NULL ) {
               ImGui::Image((ImTextureID)(intptr_t)context.scene_texture, ImVec2(context.panels.scene.width - 17, context.panels.scene.height - 40));
          }
          ImGui::EndTabItem();
     }
     if ( ImGui::BeginTabItem("Game") == true ) {
          #if 0
          ImGui::DragFloat("##originx", &viewOrigin.x, 1.0f);
          ImGui::DragFloat("##originy", &viewOrigin.y, 1.0f);
          canvas.SetView(viewOrigin, viewScale);
          if ( canvas.Begin("##mycanvas", ImVec2(context.panels.scene.width - 17, 0.0f)) ) {

               if ( ImGui::IsItemHovered() ) {
                    if ( ImGui::IsMouseDown(2) ) {
                         LOG("Dragging");
                         //ImVec2 cur_pos = ImGui::GetMousePos();

                         ImVec2 cur_pos = ImGui::GetMouseDragDelta(2);
                         LOG("cur %f new %f", mouse_pos.x, cur_pos.x);

                         if ( cur_pos.x != mouse_pos.x ) {
                              mouse_pos = ImGui::GetMouseDragDelta(2);
                              ImVec2 mouse_delta = mouse_pos;
                              ImGui::ResetMouseDragDelta(2);
                              //mouse_pos = ImGui::GetMousePos();
                              LOG("x:%f y:%f", mouse_delta.x, mouse_delta.y);
                              viewOrigin.y += (mouse_delta.y / 2);
                              viewOrigin.x += (mouse_delta.x / 2);
                         }
                    }
               }

               ImGui::Image((ImTextureID)(intptr_t)context.scene_texture, ImVec2(context.panels.scene.width - 17, context.panels.scene.height - 70));

               canvas.End();
          }
     #endif
          ImGui::EndTabItem();
     }
     ImGui::EndTabBar();
     #if 0
     float DISTANCE = 10.0f;
     ImGuiIO& io = ImGui::GetIO();
     int corner = 0;
     ImVec2 window_pos = ImVec2((corner & 1) ? io.DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? io.DisplaySize.y - DISTANCE : DISTANCE);
     ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
     ImGui::SetNextWindowBgAlpha(0.35f);
     ImGui::Begin("Stats Overlay", NULL, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav);
     ImGui::Text("FPS:");
     ImGui::End();
     #endif
     ImGui::End();
}

