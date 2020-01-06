#include <new>
#include "gui.h"
#include "imgui.h"
#include "engine_core.h"
#include "platform_graphics.h"

char gui_vert[] = "                                                        \
                    #version 330 core\n                                    \
                    layout (location = 0) in vec2 Position;\n              \
                    layout (location = 1) in vec2 UV;\n                    \
                    layout (location = 2) in vec4 Color;\n                 \
                    uniform mat4 ProjMtx;\n                                \
                    out vec2 Frag_UV;\n                                    \
                    out vec4 Frag_Color;\n                                 \
                    void main()\n                                          \
                    {\n                                                    \
                         Frag_UV = UV;\n                                   \
                         Frag_Color = Color;\n                             \
                         gl_Position = ProjMtx * vec4(Position.xy,0,1);\n  \
                    }\n                                                    \
                  ";

char gui_frag[] = "                                                                  \
                    #version 330 core\n                                              \
                    in vec2 Frag_UV;\n                                               \
                    in vec4 Frag_Color;\n                                            \
                    uniform sampler2D Texture;\n                                     \
                    out vec4 Out_Color;\n                                            \
                    void main()\n                                                    \
                    {\n                                                              \
                         Out_Color = Frag_Color * texture(Texture, Frag_UV.st);\n    \
                    }\n                                                              \
                  ";

struct Gui_Info {
     int32_t fb_width;
     int32_t fb_height;
	Engine::Shader* gui_shader;
     uint32_t vao;
     uint32_t data_vbo;
     uint32_t indice_vbo;
     int32_t attrib_pos_location;
     int32_t attrib_uv_location;
     int32_t attrib_color_location;
     int32_t proj_mtx_location;
     int32_t tex_location;
};

Gui_Info* gui_info = NULL;

void gui_key_event_callback( Engine::Key key, bool is_pressed );
void gui_mouse_pos_callback( int x_pos, int y_pos );
void gui_mouse_button_callback( int button, bool is_pressed );
void gui_resize_callback( int32_t width, int32_t height );

Engine::Rc_t init_gui( Engine::Window& window )
{
     if ( gui_info == NULL ) {
          gui_info = new (std::nothrow) Gui_Info;
          if ( gui_info == NULL ) {
               return Engine::MEMORY_ALLOC_FAILED;
          }

          int32_t fb_width = (int32_t)window.width();
          int32_t fb_height = (int32_t)window.height();

          IMGUI_CHECKVERSION();
          ImGui::CreateContext();
          ImGuiIO& io = ImGui::GetIO();
          ImGui::StyleColorsDark();

#ifdef WINDOWS
          //setup special key mappings
	  io.KeyMap[ImGuiKey_Backspace] = 8;
	  io.KeyMap[ImGuiKey_Space] = 32;
	  io.KeyMap[ImGuiKey_Enter] = 13;
#elif LINUX

#else
    #error
#endif

          io.DisplaySize = ImVec2((float)fb_width, (float)fb_height);

          io.KeyMap[ImGuiKey_Enter] = Engine::KEY_ENTER;
	     io.KeyMap[ImGuiKey_Backspace] = Engine::KEY_BACKSPACE;

          gui_info->fb_width = fb_width;
          gui_info->fb_height = fb_height;

          // setup gui font
          int32_t width;
          int32_t height;
          uint8_t* pixels;
          io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);

          Engine::Texture_Handle font_text = Engine::create_texture(width, height, pixels,Engine::Texture_Format::RGBA_FORMAT,
                                                                    Engine::Texture_Format::RGBA_FORMAT, Engine::Data_Type::UNSIGNED_BYTE);
          io.Fonts->TexID = (ImTextureID)(intptr_t)font_text;

          // setup gui shader
		std::vector<Engine::Shader_String> gui_shader_strings = {{Engine::VERTEX_SHADER, gui_vert, sizeof(gui_vert)},
												       {Engine::FRAGMENT_SHADER, gui_frag, sizeof(gui_frag)}};

		gui_info->gui_shader = new (std::nothrow) Engine::Shader(gui_shader_strings);
		if ( gui_info->gui_shader == NULL ) {
			return Engine::MEMORY_ALLOC_FAILED;
		}


          gui_info->attrib_pos_location = gui_info->gui_shader->attribute_id("Position");
          gui_info->attrib_uv_location = gui_info->gui_shader->attribute_id("UV");
          gui_info->attrib_color_location = gui_info->gui_shader->attribute_id("Color");

          gui_info->proj_mtx_location = gui_info->gui_shader->uniform_id("ProjMtx");
          gui_info->tex_location = gui_info->gui_shader->uniform_id("Texture");

          // setup vao and vbos
          gui_info->vao = Engine::create_vertex_array();
          Engine::bind_vertex_array(gui_info->vao);

          gui_info->data_vbo = Engine::create_vertex_buffer();
          Engine::bind_vertex_buffer(Engine::Buffer_Type::ARRAY_BUFFER, gui_info->data_vbo);
          Engine::enable_vertex_attrib(gui_info->attrib_pos_location);
          Engine::enable_vertex_attrib(gui_info->attrib_uv_location);
          Engine::enable_vertex_attrib(gui_info->attrib_color_location);
          Engine::define_vertex_attrib(gui_info->attrib_pos_location, 2, false, Engine::FLOAT_DATA,
                                       sizeof(ImDrawVert), (uint8_t*)IM_OFFSETOF(ImDrawVert, pos));
          Engine::define_vertex_attrib(gui_info->attrib_uv_location, 2, false, Engine::FLOAT_DATA,
                                       sizeof(ImDrawVert), (uint8_t*)IM_OFFSETOF(ImDrawVert, uv));
          Engine::define_vertex_attrib(gui_info->attrib_color_location, 4, true, Engine::UNSIGNED_BYTE,
                                       sizeof(ImDrawVert), (uint8_t*)IM_OFFSETOF(ImDrawVert, col));
          Engine::bind_vertex_buffer(Engine::Buffer_Type::ARRAY_BUFFER, 0);

          gui_info->indice_vbo = Engine::create_vertex_buffer();
          Engine::bind_vertex_buffer(Engine::Buffer_Type::ELEMENT_ARRAY_BUFFER, gui_info->indice_vbo);
          Engine::bind_vertex_buffer(Engine::Buffer_Type::ELEMENT_ARRAY_BUFFER, 0);

          Engine::bind_vertex_array(0);

          // setup gui style
          ImGui::GetStyle().WindowRounding = 0.0f;// <- Set this on init or use ImGui::PushStyleVar()
          ImGui::GetStyle().ChildRounding = 0.0f;
          ImGui::GetStyle().FrameRounding = 0.0f;
          ImGui::GetStyle().GrabRounding = 0.0f;
          ImGui::GetStyle().PopupRounding = 0.0f;
          ImGui::GetStyle().ScrollbarRounding = 0.0f;
          ImGui::GetStyle().TabRounding = 0.0f;
          ImGui::GetStyle().Alpha = 1;

          //setup callbacks
          Engine::add_key_callback(gui_key_event_callback);
          window.add_mouse_position_callback(gui_mouse_pos_callback);
          window.add_mouse_button_callback(gui_mouse_button_callback);
          window.add_resize_callback(gui_resize_callback);
     }

     return Engine::SUCCESS;
}

void gui_start_frame( void )
{
     ImGui::NewFrame();
}

Engine::Rc_t render_gui( void )
{
     ImGui::Render();
     ImDrawData* draw_data = ImGui::GetDrawData();

     int fb_width = (int)(draw_data->DisplaySize.x * draw_data->FramebufferScale.x);
     int fb_height = (int)(draw_data->DisplaySize.y * draw_data->FramebufferScale.y);

     if ( fb_width <= 0 || fb_height <= 0 ) {
          return Engine::SUCCESS;
     }

     ImVec2 clip_off = draw_data->DisplayPos;
     ImVec2 clip_scale = draw_data->FramebufferScale;

     Engine::enable_graphics_option(Engine::BLEND_OPTION);
     //TODO(JOSH): add in blend funcs below
     //gl_BlendEquation(GL_FUNC_ADD);
     //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     Engine::disable_graphics_option(Engine::DEPTH_TEST_OPTION);
     Engine::disable_graphics_option(Engine::CULL_FACE_OPTION);
     Engine::enable_graphics_option(Engine::SCISSOR_TEST_OPTION);

     Engine::set_view_port(0, 0, fb_width, fb_height);

     float L = draw_data->DisplayPos.x;
     float R = draw_data->DisplayPos.x + draw_data->DisplaySize.x;
     float T = draw_data->DisplayPos.y;
     float B = draw_data->DisplayPos.y + draw_data->DisplaySize.y;

     const float tmp_ortho_projection[4][4] =
     {
          { 2.0f/(R-L),   0.0f,         0.0f,   0.0f },
          { 0.0f,         2.0f/(T-B),   0.0f,   0.0f },
          { 0.0f,         0.0f,        -1.0f,   0.0f },
          { (R+L)/(L-R),  (T+B)/(B-T),  0.0f,   1.0f },
     };

     Engine::use_program(gui_info->gui_shader->id());

     Engine::Matrix4f test( Engine::Vector4f(2.0f/(R-L),   0.0f,         0.0f,   0.0f),
                            Engine::Vector4f(0.0f,         2.0f/(T-B),   0.0f,   0.0f),
                            Engine::Vector4f(0.0f,         0.0f,        -1.0f,   0.0f),
                            Engine::Vector4f((R+L)/(L-R),  (T+B)/(B-T),  0.0f,   1.0f) );

     gui_info->gui_shader->set_uniform_int1(gui_info->tex_location, 0);
     gui_info->gui_shader->set_uniform_mat4(gui_info->proj_mtx_location, (Engine::Matrix4f*)&test);

     Engine::bind_vertex_array(gui_info->vao);
     Engine::bind_vertex_buffer(Engine::Buffer_Type::ARRAY_BUFFER, gui_info->data_vbo);
     Engine::bind_vertex_buffer(Engine::Buffer_Type::ELEMENT_ARRAY_BUFFER, gui_info->indice_vbo);

     for ( int ii = 0; ii < draw_data->CmdListsCount; ii++ ) {
          const ImDrawList* cmd_list = draw_data->CmdLists[ii];

          Engine::buffer_vertex_data(Engine::ARRAY_BUFFER, (uint8_t*)cmd_list->VtxBuffer.Data,
                                     cmd_list->VtxBuffer.Size * sizeof(ImDrawVert), Engine::STREAM_DRAW);

          Engine::buffer_vertex_data(Engine::ELEMENT_ARRAY_BUFFER, (uint8_t*)cmd_list->IdxBuffer.Data,
                                     cmd_list->IdxBuffer.Size * sizeof(ImDrawIdx), Engine::STREAM_DRAW);

          for ( int jj = 0; jj < cmd_list->CmdBuffer.Size; jj++ ) {
               const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[jj];

               ImVec4 clip_rect;
               clip_rect.x = (pcmd->ClipRect.x - clip_off.x) * clip_scale.x;
               clip_rect.y = (pcmd->ClipRect.y - clip_off.y) * clip_scale.y;
               clip_rect.z = (pcmd->ClipRect.z - clip_off.x) * clip_scale.x;
               clip_rect.w = (pcmd->ClipRect.w - clip_off.y) * clip_scale.y;

               if ( clip_rect.x < fb_width && clip_rect.y < fb_height && clip_rect.z >= 0.0f && clip_rect.w >= 0.0f ) {
                    Engine::scissor_box((int)clip_rect.x, (int)(fb_height - clip_rect.w),
                                        (int)(clip_rect.z - clip_rect.x), (int)(clip_rect.w - clip_rect.y));
               }

               Engine::bind_texture((int)(intptr_t)pcmd->TextureId);

               Engine::draw_elements_data(Engine::TRIANGLE_MODE, pcmd->ElemCount,
                                          (sizeof(ImDrawIdx) == 2 ? Engine::UNSIGNED_SHORT : Engine::UNSIGNED_INT),
                                          (void*)(intptr_t)(pcmd->IdxOffset * sizeof(ImDrawIdx)));
          }
     }

     Engine::bind_vertex_array(0);

     Engine::disable_graphics_option(Engine::BLEND_OPTION);
     Engine::enable_graphics_option(Engine::DEPTH_TEST_OPTION);
     Engine::enable_graphics_option(Engine::CULL_FACE_OPTION);
     Engine::disable_graphics_option(Engine::SCISSOR_TEST_OPTION);

     return Engine::SUCCESS;
}

void gui_key_event_callback( Engine::Key key, bool is_pressed )
{
     ImGuiIO& io = ImGui::GetIO();

     if ( is_pressed == true ) {
          char c_key = Engine::key_to_char(key);
          if ( c_key != -1 ) {
               io.AddInputCharacter(c_key);
          }

	     io.KeysDown[key] = true;
     } else {
	     io.KeysDown[key] = false;
     }

     io.KeyShift = io.KeysDown[16];
}

void gui_mouse_pos_callback( int x_pos, int y_pos )
{
     ImGuiIO& io = ImGui::GetIO();

     io.MousePos = ImVec2((float)x_pos, (float)y_pos);
}

void gui_mouse_button_callback( int button, bool is_pressed )
{
     ImGuiIO& io = ImGui::GetIO();

     if ( is_pressed == true ) {
          io.MouseDown[button - 1] = true;
     } else {
          io.MouseDown[button - 1] = false;
     }
}

void gui_resize_callback( int32_t width, int32_t height )
{
     ImGuiIO& io = ImGui::GetIO();

     io.DisplaySize = ImVec2((float)width, (float)height);

     Engine::delete_texture((Engine::Texture_Handle)(intptr_t)io.Fonts->TexID);
     int32_t lwidth;
     int32_t lheight;
     uint8_t* pixels;
     io.Fonts->GetTexDataAsRGBA32(&pixels, &lwidth, &lheight);

     Engine::Texture_Handle font_text = Engine::create_texture(lwidth, lheight, pixels, Engine::Texture_Format::RGBA_FORMAT,
                                                               Engine::Texture_Format::RGBA_FORMAT, Engine::Data_Type::UNSIGNED_BYTE);
     io.Fonts->TexID = (ImTextureID)(intptr_t)font_text;
}

