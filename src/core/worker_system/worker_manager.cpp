#include "worker_manager.h"

namespace core {

namespace Worker_Manager {

#define MAX_WORKER_THREADS  8
#define STARTING_CORE       2

void worker_thread( void* data );

typedef struct {
    std::vector<thread_data_t> _thread_data_vec;
} worker_manager_t;

worker_manager_t worker_manager;

UhRC_t init( void )
{
    LOG("Moving the Main Thread to CPU 1");
    //IMPORTANT never want to run on CPU 0
    //SetThreadAffinityMask(GetCurrentThread(), (uint32_t)(1 << 1));
    set_thread_affinity(1);

    uint32_t core_count = core::get_logical_core_count();
    LOG("System Core Count: " << core_count);

    switch( core_count ) {
    case 1: {
        return ENGINE_ERROR;
    } break;
    case 2: {

    } break;
    case 3:
    case 4: {

        uint32_t worker_count = core_count;

        LOG("Worker_Manager Starting " << worker_count - 1 << " workers");
        worker_manager._thread_data_vec.resize(worker_count);

        worker_manager._thread_data_vec[0].cpu = 0;
        worker_manager._thread_data_vec[0].function = worker_thread;
        core::create_thread(&worker_manager._thread_data_vec[0]);
        LOG("Worker_Manager Starting Worker on CPU 0");

        uint8_t current_cpu = 2;

        for (uint8_t ii = 2; ii < worker_manager._thread_data_vec.size(); ii++) {
            LOG("Worker_Manager Starting Worker on CPU " << (int)current_cpu);
            worker_manager._thread_data_vec[ii].cpu = current_cpu++;
            worker_manager._thread_data_vec[ii].function = worker_thread;

            core::create_thread(&worker_manager._thread_data_vec[ii]);
        }
    } break;
    default: {

        uint32_t possible_worker_count = core_count - 2;
        uint32_t worker_count = possible_worker_count > MAX_WORKER_THREADS ? possible_worker_count : possible_worker_count;
        uint8_t current_cpu = STARTING_CORE;

        LOG("Worker_Manager Starting " << worker_count << " workers");
        worker_manager._thread_data_vec.resize(worker_count);
        for (uint8_t ii = 0; ii < worker_manager._thread_data_vec.size(); ii++) {
            LOG("Worker_Manager Starting Worker on CPU " << (int)current_cpu);
            worker_manager._thread_data_vec[ii].cpu = current_cpu++;
            worker_manager._thread_data_vec[ii].function = worker_thread;

            core::create_thread(&worker_manager._thread_data_vec[ii]);
        }
    }
    };

    return SUCCESS;
}

void worker_thread( void* data )
{
    //thread_data_t* thread_data = (thread_data_t*)data;
    job_node_t job_node;
    while(true) {
        if ( Job_Manager::get_next_job(&job_node) == true ) {
            job_node.job.Execute();
            Job_Manager::complete_job(job_node.handle);
        } else {
            //Sleep(1);
            std::this_thread::sleep_for(std::chrono::microseconds(1));
        }
    }
}

} // end namespace Worker_Manager
} // end namespace core
