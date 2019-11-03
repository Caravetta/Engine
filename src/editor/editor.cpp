#include "gui.h"
#include "engine_core.h"

#define WINDOW_WIDTH     800
#define WINDOW_HEIGHT    600

void key_test( char key, bool is_pressed )
{
     LOG("JOSH %c", key);
}

int main()
{
     Engine::Rc_t rc = Engine::engine_init();
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("Failed to init engine rc=%d", rc);
          return -1;
     }

     Engine::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Test");

     rc = init_gui(WINDOW_WIDTH, WINDOW_HEIGHT);
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("init_gui failed rc=%d", (int)rc);
          return -1;
     }

     window.add_key_callback(key_test);
     window.add_key_callback(gui_key_event_callback);
     window.add_mouse_position_callback(gui_mouse_pos_callback);
     window.add_mouse_button_callback(gui_mouse_button_callback);
     window.add_resize_callback(gui_resize_callback);

     Engine::set_clear_color(0.5f, 0.6f, 0.7f, 1.0f);

     while ( window.is_closed() == false ) {
          window.update();

          Engine::graphics_clear(Engine::COLOR_BUFFER_CLEAR | Engine::DEPTH_BUFFER_CLEAR);

          gui_start_frame();

          ImGui::Begin("Hello, world!");

          ImGui::Text("This is some useful text.");

          ImGui::End();

          render_gui();

          window.swap_buffers();
     }

     return 0;
}

