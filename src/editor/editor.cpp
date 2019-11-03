#include "gui.h"
#include "engine_core.h"
#include "entity_manager.h"

#define WINDOW_WIDTH     800
#define WINDOW_HEIGHT    600

std::vector<Engine::Render_Texture*> render_textures;

void fb_resize_callback( int32_t width, int32_t height )
{
     for ( size_t ii = 0; ii < render_textures.size(); ii++ ) {
          render_textures[ii]->reload(width, height);
     }
}

int main()
{
     Engine::Rc_t rc = Engine::engine_init();
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("Failed to init engine rc=%d", rc);
          return -1;
     }

     Engine::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Editor");

     rc = init_gui(window);
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("init_gui failed rc=%d", (int)rc);
          return -1;
     }

     window.add_resize_callback(fb_resize_callback);

     Entity_Manager entity_manager;

     Engine::set_clear_color(0.5f, 0.6f, 0.7f, 1.0f);

     // TODO(JOSH): need to move this
     Engine::Render_Texture_Info texture_info(window.width(), window.height(), Engine::Texture_Format::RGB_FORMAT);
     Engine::Render_Texture base(texture_info);
     Engine::Render_Texture_Info gui_texture_info(window.width(), window.height(), Engine::Texture_Format::RGB_FORMAT);
     Engine::Render_Texture gui_base(gui_texture_info);
     Engine::Render_Context render_context;
     render_textures.push_back(&base);
     render_textures.push_back(&gui_base);
     render_context.init();

     size_t selected = 100000000;
     bool entity_selected = false;

     float button_width = 0;
     bool add_comp = false;

     while ( window.is_closed() == false ) {
          window.update();

          // update gui settings
          float console_tab_height = (float)(window.height() * 0.3);
          float instector_tab_width = (float)(window.width() * 0.2);
          float hierarchy_tab_width = (float)(window.width() * 0.15);
          float scene_x_pos = hierarchy_tab_width;
          float scene_y_pos = 19;
          float scene_width = (float)window.width() - instector_tab_width - hierarchy_tab_width;
          float scene_height = (float)window.height() - 19 - console_tab_height;

          //render game here to texture
          Engine::enable_graphics_option(Engine::DEPTH_TEST_OPTION);
          Engine::set_depth_func(Engine::DEPTH_LESS_FUNC);

          render_context.bind();
          render_context.set_color_texture(base);

          Engine::set_view_port(0, 0, window.width(), window.height());

          Engine::graphics_clear(Engine::COLOR_BUFFER_CLEAR | Engine::DEPTH_BUFFER_CLEAR);

          Engine::Render_Texture& end_texure = render_context.cur_color_texture();
          render_context.set_color_texture(gui_base);
          gui_start_frame();

          ImGui::SetNextWindowBgAlpha(1);
          ImGui::SetNextWindowPos(ImVec2(-1, 0));
          ImGui::SetNextWindowSize(ImVec2((float)window.width() + 2, 0.0f));
          ImGui::Begin("Menu", NULL, ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar |
                                     ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |
                                     ImGuiWindowFlags_NoBackground);
          ImGui::BeginMenuBar();
          if ( ImGui::BeginMenu("File", true) ) {
               if ( ImGui::MenuItem("Exit") == true ) {
                    break;
               }
               ImGui::EndMenu();
          }
          if ( ImGui::BeginMenu("Edit", true) ) {
               if ( ImGui::BeginMenu("Test") ) {
                    if ( ImGui::MenuItem("Test1") == true ) {
                    }
                    ImGui::EndMenu();

               }
               ImGui::EndMenu();
          }
          if ( ImGui::BeginMenu("GameObjects", true) ) {
               if ( ImGui::BeginMenu("Create") ) {
                    if ( ImGui::MenuItem("Entity") == true ) {
                         entity_manager.create_entity();
                    }
                    ImGui::EndMenu();

               }
               ImGui::EndMenu();
          }
          ImGui::EndMenuBar();
          ImGui::End();

          //console tab
          ImGui::SetNextWindowPos(ImVec2(0, (float)window.height() - console_tab_height));
          ImGui::SetNextWindowSize(ImVec2((float)window.width() - instector_tab_width, console_tab_height));
          ImGui::Begin("Console", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
          ImGui::BeginTabBar("Tabs");
          if ( ImGui::BeginTabItem("Console") == true ) {
               ImGui::EndTabItem();
          }
          if ( ImGui::BeginTabItem("Performace") == true ) {
               ImGui::EndTabItem();
          }
          ImGui::EndTabBar();
          ImGui::End();

          //inspector tab
          ImGui::SetNextWindowPos(ImVec2((float)window.width() - instector_tab_width, 19));
          ImGui::SetNextWindowSize(ImVec2(instector_tab_width, (float)window.height()));
          ImGui::Begin("Inspector", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
          ImGui::BeginTabBar("Tabs");
          if ( ImGui::BeginTabItem("Inspector") == true ) {
               if ( entity_selected ) {
                    //ImGui::Indent((instector_tab_width / 2) - button_width);
                    if ( ImGui::Button("Add Component", ImVec2(instector_tab_width, 0)) ) {
                         add_comp = true;
                    }

                    ImVec2 aa = ImGui::GetItemRectSize();

                    if ( add_comp ) {
                         ImGui::SetNextWindowSize(ImVec2(instector_tab_width - 12, 300));
                         ImGui::SetNextWindowPos(ImVec2((float)window.width() - instector_tab_width + 8, 70));
                         ImGui::Begin("End", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
                         if (  !ImGui::IsWindowFocused() ) {
                              add_comp = false;
                         }
                         ImGui::End();

                    }
               }
               ImGui::EndTabItem();
          }
          ImGui::EndTabBar();
          ImGui::End();

          //hierarchy tab
          ImGui::SetNextWindowPos(ImVec2(0, 19));
          ImGui::SetNextWindowSize(ImVec2(hierarchy_tab_width, (float)window.height() - 19 - console_tab_height));
          ImGui::Begin("Hierarchy", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
          ImGui::BeginTabBar("Tabs");
          if ( ImGui::BeginTabItem("Hierarchy") == true ) {
               std::vector<std::string> entities = entity_manager.get_entity_name_list();
               for ( size_t ii = 0; ii < entities.size(); ii++ ) {
                    if ( ImGui::Selectable(entities[ii].c_str(), (ii == selected ? true : false) ) == true ) {
                         selected = ii;
                         entity_selected = true;
                    }
               }
               ImGui::EndTabItem();
          }
          ImGui::EndTabBar();
          ImGui::End();

          //scene tab
          ImGui::SetNextWindowPos(ImVec2(scene_x_pos, scene_y_pos));
          ImGui::SetNextWindowSize(ImVec2(scene_width, scene_height));
          ImGui::Begin("Scene", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
          ImGui::BeginTabBar("Tabs");
          if ( ImGui::BeginTabItem("Scene") == true ) {
               ImGui::Image((ImTextureID)(intptr_t)end_texure.texture(), ImVec2(scene_width - 17, scene_height - 40));
               ImGui::EndTabItem();
          }
          if ( ImGui::BeginTabItem("Game") == true ) {
               ImGui::EndTabItem();
          }
          ImGui::EndTabBar();
          ImGui::End();


          render_gui();

          render_context.bit_to_screen();

          window.swap_buffers();
     }

     return 0;
}

