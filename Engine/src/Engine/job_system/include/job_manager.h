#ifndef __JOB_MANAGER_H__
#define __JOB_MANAGER_H__

#include <functional>
#include "core_common.h"

namespace Engine {

//typedef base_handle_t Job_Handle;
typedef struct {
    union {
        struct {
            uint64_t index  : 32;
            uint64_t phase  : 31;
            uint64_t active : 1;
        };
        uint64_t id;
    };
} Job_Handle;

struct Base_Job {
    std::function<void()> Execute;
};

typedef struct {
    Job_Handle  handle;
    Base_Job    job;
} job_node_t;

namespace Job_Manager {

Rc_t init( void );
Job_Handle get_job_handle( void );
Rc_t register_job( Job_Handle job_handle, std::function<void()> execute );
bool is_job_complete( Job_Handle job_handle );
bool get_next_job( job_node_t* job_node );
Rc_t complete_job( Job_Handle job_handle );

} // end namespace Job_Manager
} // end namespace Engine

#endif //__JOB_MANAGER_H__
