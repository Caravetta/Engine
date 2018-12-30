#include <stdint.h>
#include <string>
#include "platform.h"
#include "input_manager.h"

namespace Engine {

#define CHECK_SDL_ERROR() {                 \
    const char* error = SDL_GetError();     \
    if ( *error != '\0' ) {                 \
        LOG_ERROR(error);                   \
        SDL_ClearError();                   \
        return ENGINE_ERROR;                \
    }                                       \
}

struct platform_window_t {
    int             width;
    int             height;
    int             show;
    std::string     title;
    SDL_Window*     handle;
    SDL_GLContext   context;
    bool            is_closed;
};

Rc_t _init( struct platform_window_t* window );

void platform_window_update( struct platform_window_t* platform_window )
{
    SDL_Event event;

    while ( SDL_PollEvent(&event) ) {
        switch( event.type ) {
        case SDL_QUIT: {
            platform_window->is_closed = true;
        } break;
        case SDL_KEYDOWN: {
            Input_Manager::get_instance()->process_key_down(
                (key_id_t) event.key.keysym.scancode, (uint16_t) event.key.keysym.sym);
        } break;
        case SDL_KEYUP: {
            Input_Manager::get_instance()->process_key_up(
                (key_id_t) event.key.keysym.scancode, (uint16_t) event.key.keysym.sym);
        } break;

        }
    }

    return;
}

struct platform_window_t* platform_window_create( int width, int height, std::string title )
{
    struct platform_window_t* window = new platform_window_t;
    window->width = width;
    window->height = height;
    window->title = title;
    window->is_closed = false;

    Rc_t rc = _init(window);
    if ( rc != SUCCESS ) {
        delete window;
        return NULL;
    }

    return window;
}

Rc_t _init( struct platform_window_t* window )
{
    Rc_t rc = SUCCESS;

    if ( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
        LOG_ERROR("Failed to Init SDL");
        return ENGINE_ERROR;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

    window->handle = SDL_CreateWindow(window->title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                      window->width, window->height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    CHECK_SDL_ERROR();
    if ( window->handle == NULL ) {
        LOG_ERROR("Failed to create window");
        return ENGINE_ERROR;
    }

    window->context = SDL_GL_CreateContext(window->handle);
    CHECK_SDL_ERROR();

    glewExperimental = true;
    if ( glewInit() != GLEW_OK ) {
        LOG_ERROR("Failed to map OpenGL function");
        return ENGINE_ERROR;
    }

    return SUCCESS;
}

void platform_window_swap_buffers( struct platform_window_t* platform_window )
{
    SDL_GL_SwapWindow(platform_window->handle);
}

int platform_window_get_width( struct platform_window_t* platform_window )
{
    return platform_window->width;
}

int platform_window_get_height( struct platform_window_t* platform_window )
{
    return platform_window->height;
}

bool platform_window_is_closed( struct platform_window_t* platform_window )
{
    return platform_window->is_closed;
}

} //end namespace Engine
