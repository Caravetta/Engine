#include "job_manager.h"
#include "thread.h"

namespace Engine {
namespace Job_Manager {

#define MAX_JOB_QUEUE_SIZE 500

typedef struct {
    uint16_t parts;
    uint16_t complete_parts;
} job_info_node_t;

typedef struct {
    std::vector<job_node_t> data;
    bool                    empty;
    bool                    full;
    uint16_t                head;
    uint16_t                tail;
    lock_t                  lock;
} job_queue_t;

typedef struct {
    std::vector<job_info_node_t>    _job_data_vec;
    std::vector<Job_Handle>         _job_handle_vec;
    std::vector<uint32_t>           _free_handle_vec;
    uint64_t                        _next_handle_idx;
    job_queue_t                     _job_queue;
    lock_t                          _job_data_lock;
    lock_t                          _job_handle_lock;
    //CONDITION_VARIABLE              _conditionVar;    //TODO(JOSH): need to move this win to platform level
} job_manager_t;

job_manager_t job_manager;

Rc_t init( void )
{
    Rc_t rc;

    rc = init_lock(&job_manager._job_data_lock);
    if ( rc != SUCCESS ) {
        return ENGINE_ERROR;
    }

    rc = init_lock(&job_manager._job_handle_lock);
    if ( rc != SUCCESS ) {
        return ENGINE_ERROR;
    }

    rc = init_lock(&job_manager._job_queue.lock);
    if ( rc != SUCCESS ) {
        return ENGINE_ERROR;
    }

    //InitializeConditionVariable (&job_manager._conditionVar);

    job_manager._job_queue.head = 0;
    job_manager._job_queue.tail = 0;
    job_manager._job_queue.empty = true;
    job_manager._job_queue.full = false;
    job_manager._next_handle_idx = 0;

    job_manager._job_data_vec.resize(MAX_JOB_QUEUE_SIZE);
    job_manager._job_handle_vec.resize(MAX_JOB_QUEUE_SIZE);
    job_manager._job_queue.data.resize(MAX_JOB_QUEUE_SIZE);

    for (uint64_t ii = 0; ii < job_manager._job_handle_vec.size(); ii++) {
            job_manager._job_handle_vec[ii].active = HANDLE_SET_NON_ACTIVE;
            job_manager._job_handle_vec[ii].index = ii;
    }

    return SUCCESS;
}

Job_Handle get_job_handle( void )
{
    Job_Handle handle;

    get_lock(&job_manager._job_handle_lock);

    bool set = false;
    if ( !job_manager._free_handle_vec.empty() ) {
        uint32_t free_idx = job_manager._free_handle_vec.back();
        job_manager._free_handle_vec.pop_back();

        handle = job_manager._job_handle_vec[free_idx];
    } else {
        CHECK_INFO( job_manager._next_handle_idx != MAX_JOB_QUEUE_SIZE, "Run out of Job Handles" );
        CHECK_INFO( set != false , "Run out of Job Handles" );
        handle = job_manager._job_handle_vec[job_manager._next_handle_idx];
        job_manager._next_handle_idx += 1;
    }

    release_lock(&job_manager._job_handle_lock);

    if ( set ) {
        get_lock(&job_manager._job_data_lock);

        job_manager._job_data_vec[handle.index].parts = 0;
        job_manager._job_data_vec[handle.index].complete_parts = 0;

        release_lock(&job_manager._job_data_lock);
    }

    return handle;
}

Rc_t register_job( Job_Handle job_handle, std::function<void()> execute )
{
    get_lock(&job_manager._job_queue.lock);
    get_lock(&job_manager._job_data_lock);

    if ( job_manager._job_queue.full ) {
        release_lock(&job_manager._job_data_lock);
        release_lock(&job_manager._job_queue.lock);
        CHECK_INFO( 0, "Run out of room in the Job queue");
        return ENGINE_ERROR; //TODO(JOSH): need to make a real error return
    }

    job_manager._job_data_vec[job_handle.index].parts += 1;

     job_manager._job_queue.data[job_manager._job_queue.tail].handle = job_handle;
    job_manager._job_queue.data[job_manager._job_queue.tail++].job.Execute = execute;

    job_manager._job_queue.empty = false;

    if ( job_manager._job_queue.tail == MAX_JOB_QUEUE_SIZE ) {
        job_manager._job_queue.tail = 0;
    }

    if ( job_manager._job_queue.tail == job_manager._job_queue.head ) {
        job_manager._job_queue.full = true;
    }

    release_lock(&job_manager._job_data_lock);
    release_lock(&job_manager._job_queue.lock);

    return SUCCESS;
}

bool is_job_complete( Job_Handle job_handle )
{
    bool is_complete = false;

    get_lock(&job_manager._job_data_lock);
    if ( job_manager._job_data_vec[job_handle.index].parts == job_manager._job_data_vec[job_handle.index].complete_parts ) {
        is_complete = true;
    }
    release_lock(&job_manager._job_data_lock);

    if ( is_complete == true ) {
        get_lock(&job_manager._job_handle_lock);
        job_manager._free_handle_vec.push_back(job_handle.index);
        release_lock(&job_manager._job_handle_lock);
    }

    return is_complete;
}

bool get_next_job( job_node_t* job_node )
{
    get_lock(&job_manager._job_queue.lock);
    if ( job_manager._job_queue.empty ) {
        release_lock(&job_manager._job_queue.lock);
        return false;
    }

    *job_node = job_manager._job_queue.data[job_manager._job_queue.head++];

    if ( job_manager._job_queue.head == MAX_JOB_QUEUE_SIZE ) {
        job_manager._job_queue.head = 0;
    }

    job_manager._job_queue.full = false;

    if ( job_manager._job_queue.tail == job_manager._job_queue.head ) {
        job_manager._job_queue.empty = true;
    }

    release_lock(&job_manager._job_queue.lock);

    return true;
}

Rc_t complete_job( Job_Handle job_handle )
{
    get_lock(&job_manager._job_data_lock);
    job_manager._job_data_vec[job_handle.index].complete_parts++;
    release_lock(&job_manager._job_data_lock);

    return SUCCESS;
}

} // end namespace Job_Manager
} // end namespace Engine
