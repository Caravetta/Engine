#include <errno.h>
#include <pthread.h>
#include <string.h>

#include "thread_linux.h"

namespace Engine {

Rc_t platform_init_lock( platform_lock_t *lock ) {
    int rc = pthread_spin_init( lock, PTHREAD_PROCESS_PRIVATE );
    if ( rc ) {
        LOG_ERROR( strerror( rc ) );
        return ENGINE_ERROR;
    }
    return SUCCESS;
}

void platform_get_lock( platform_lock_t *lock ) {
#ifdef DEBUG_LOCKING
    cpu_set_t cpuset;
    CPU_ZERO( &cpuset );
    pthread_t thread = pthread_self();
    pthread_getaffinity_np( thread, sizeof( cpuset ), &cpuset );
    for ( int ii = 0; ii < CPU_SETSIZE; ii++ ) {
        if ( CPU_ISSET( ii, &cpuset ) ) {
            printf( "    CPU %d getting lock\n", ii );
        }
    }
#endif
    errno = pthread_spin_lock( lock );
    CHECK_INFO( errno == 0, perror( __FUNCTION__ ) );
}

void platform_release_lock( platform_lock_t *lock ) {
    errno = pthread_spin_unlock( lock );
    CHECK_INFO( errno == 0, perror( __FUNCTION__ ) );
}

static void *MyThreadFunction( void *arg ) {
    thread_data_window_t *thread_data = (thread_data_window_t *)arg;

    platform_set_thread_affinity( thread_data->cpu );
    thread_data->function( (void *)arg );

    return 0;
}

void platform_create_thread( thread_data_window_t *thread_data ) {
    int rc =
        pthread_create( &thread_data->thread_handle, NULL, &MyThreadFunction, thread_data );

    if ( rc ) {
        LOG_ERROR( "Failed to create thread" );
    }
}

void platform_set_thread_affinity( uint8_t cpu ) {
    cpu_set_t cpuset;
    pthread_t thread;

    thread = pthread_self();

    CPU_ZERO( &cpuset );
    CPU_SET( cpu, &cpuset );

    errno = pthread_setaffinity_np( thread, sizeof( cpu_set_t ), &cpuset );
    if ( errno != 0 ) {
        perror( __FUNCTION__ );
    }
}

} // end namespace Engine
