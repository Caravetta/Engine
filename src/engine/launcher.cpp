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

        START_TIME_BLOCK(engine_update);
    while( !engine->window->is_closed() ) {
        //START_TIME_BLOCK(engine_update);
        engine->update();
    }

    engine->shutdown();

    return 0;
}
