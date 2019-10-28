#include "gui.h"
#include "imgui.h"
#include "platform_graphics.h"

Engine::Rc_t init_gui( void )
{
     IMGUI_CHECKVERSION();
     ImGui::CreateContext();
     ImGuiIO& io = ImGui::GetIO();
     ImGui::StyleColorsDark();

     int width;
     int height;
     unsigned char* pixels;
     io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

     Engine::Texture_Handle font_text = Engine::create_texture(width, height, pixels, Engine::Texture_Format::RGBA_FORMAT);

     io.Fonts->TexID = (ImTextureID)(intptr_t)font_text;
     Engine::bind_texture(font_text);

     return Engine::SUCCESS;
}

Engine::Rc_t render_gui( void )
{
     ImGui::Render();
     ImDrawData* draw_data = ImGui::GetDrawData();

     int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
     int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);

     return Engine::SUCCESS;
}

