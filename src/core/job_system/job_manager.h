#ifndef __JOB_MANAGER_H__
#define __JOB_MANAGER_H__

#include <functional>
#include "../core_common.h"

namespace core {

typedef base_handle_t Job_Handle;

struct Base_Job {
    std::function<void()> Execute;
};

typedef struct {
    Job_Handle  handle;
    Base_Job    job;
} job_node_t;

namespace Job_Manager {

CORE_API UhRC_t init( void );
CORE_API Job_Handle get_job_handle( void );
CORE_API UhRC_t register_job( Job_Handle job_handle, std::function<void()> execute );
CORE_API bool is_job_complete( Job_Handle job_handle );
CORE_API bool get_next_job( job_node_t* job_node );
CORE_API UhRC_t complete_job( Job_Handle job_handle );

} // end namespace Job_Manager
} // end namespace core

#endif //__JOB_MANAGER_H__
