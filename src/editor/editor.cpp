#include "gui.h"
#include "editor_context.h"
#include "engine_core.h"
#include "entity_manager.h"
#include "panels.h"
#include "cube.h"
#ifdef WINDOWS
#include <windows.h>
#endif

#define WINDOW_WIDTH     1600
#define WINDOW_HEIGHT    1000

std::vector<Engine::Render_Texture*> render_textures;

void fb_resize_callback( int32_t width, int32_t height )
{
     for ( size_t ii = 0; ii < render_textures.size(); ii++ ) {
          render_textures[ii]->reload(width, height);
     }
}

#ifdef WINDOWS
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpCmdLine, INT nCmdShow)
#else
int main( void )
#endif
{
     Engine::Rc_t rc = Engine::engine_init();
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("Failed to init engine rc=%d", rc);
          return -1;
     }

     Editor_Context& editor_context = *Editor_Context::get_instance();

     editor_context.window = new (std::nothrow) Engine::Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Editor");
     if ( editor_context.window == NULL ) {
          LOG_ERROR("Failed to create window");
          return -1;
     }

     rc = init_gui(*editor_context.window);
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("init_gui failed rc=%d", (int)rc);
          return -1;
     }

     load_cube_mesh();

     init_panels(editor_context);
     editor_context.window->add_resize_callback(fb_resize_callback);
     editor_context.component_list = Engine::get_component_list();

     // TODO(JOSH): need to move this
     Engine::Render_Texture_Info texture_info(editor_context.window->width(), editor_context.window->height(), Engine::Texture_Format::RGB_FORMAT);
     Engine::Render_Texture base(texture_info);
     Engine::Render_Texture_Info gui_texture_info(editor_context.window->width(), editor_context.window->height(), Engine::Texture_Format::RGB_FORMAT);
     Engine::Render_Texture gui_base(gui_texture_info);
     Engine::Render_Context render_context;
     render_textures.push_back(&base);
     render_textures.push_back(&gui_base);
     render_context.init();

     Engine::set_clear_color(0.5f, 0.6f, 0.7f, 1.0f);

     while ( editor_context.window->is_closed() == false ) {
          editor_context.window->update();

          //render game here to texture
          Engine::enable_graphics_option(Engine::DEPTH_TEST_OPTION);
          Engine::set_depth_func(Engine::DEPTH_LESS_FUNC);

          render_context.bind();
          render_context.set_color_texture(base);

          //Engine::set_view_port(0, 0, window.width(), window.height());

          Engine::graphics_clear(Engine::COLOR_BUFFER_CLEAR | Engine::DEPTH_BUFFER_CLEAR);

          // start render here

          Engine::Render_Texture& end_texure = render_context.cur_color_texture();

          editor_context.scene_texture = end_texure.texture();
          render_context.set_color_texture(gui_base);
          update_panels(editor_context);
          render_gui();
          render_context.bit_to_screen();
          editor_context.window->swap_buffers();
     }

     return 0;
}

