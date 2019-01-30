#include "thread.h"

namespace Engine {

Rc_t init_lock( lock_t* lock )
{
    return platform_init_lock((platform_lock_t*)lock);
}

void get_lock( lock_t* lock )
{
    platform_get_lock((platform_lock_t*)lock);
}

void release_lock( lock_t* lock )
{
    platform_release_lock((platform_lock_t*)lock);
}

void create_thread( thread_data_t* thread_data )
{
    platform_create_thread((thread_data_window_t*)thread_data);
}

void set_thread_affinity( uint8_t cpu )
{
    platform_set_thread_affinity(cpu);
}

} // end namespace Engine
