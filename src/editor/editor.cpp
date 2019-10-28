#include "gui.h"
#include "engine_core.h"

#define WINDOW_WIDTH     800
#define WINDOW_HEIGHT    600

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
                  ";                                                                 \

int main()
{
     Engine::Rc_t rc = Engine::engine_init();
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("Failed to init engine rc=%d", rc);
          return -1;
     }

     Engine::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Test");

     rc = init_gui();
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("init_gui failed rc=%d", (int)rc);
          return -1;
     }

     std::vector<Engine::Shader_String> gui_shader_strings = {{Engine::VERTEX_SHADER, gui_vert, sizeof(gui_vert)},
                                                              {Engine::FRAGMENT_SHADER, gui_frag, sizeof(gui_frag)}};

     Engine::Shader gui_shader(gui_shader_strings);

     while ( window.is_closed() == false ) {
          window.update();

          window.swap_buffers();
     }

     return 0;
}

