#include "engine.h"
#include "engine.cpp"
#include "../core/core.h"

//DWORD     --- uint32_t
//DWORD_PTR --- uint64_t
//HANDLE    --- void*
//LPVOID    --- void*

int main()
{
    Engine* engine = Engine::get_instance();

    engine->init();

    while( !engine->window->is_closed() ) {
        engine->update();
    }

    engine->shutdown();

    return 0;
}
