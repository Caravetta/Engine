#include "thread.h"
#include "win_32/thread/thread_win32.h"

namespace core {

void create_thread( thread_data_t* thread_data )
{
    platform_create_thread((thread_data_window_t*)thread_data);
}

} // end namespace core
