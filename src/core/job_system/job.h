#ifndef __JOB_H__
#define __JOB_H__

#include <functional>
#include "../core_common.h"
#include "job_manager.h"

namespace core {

struct Job_Loop {
private:
    uint64_t _iteration_count;
    uint64_t _block_count;
public:
    Job_Handle Schedule( uint64_t iterations, uint64_t block_count );
    virtual void Execute( uint64_t index ) = 0;
};

Job_Handle Job_Loop::Schedule( uint64_t iterations, uint64_t block_count )
{
    CHECK_INFO( iterations != 0, "Can not have zero iterations" );
    CHECK_INFO( block_count != 0, "Can not have zero block_count" );

    //calculate number of jobs to spawn
    uint64_t num_jobs;
    if ( iterations > block_count ) {
        num_jobs = iterations / block_count;
    } else {
        num_jobs = 1;
    }

    Job_Handle job_handle = Job_Manager::get_job_handle();

    uint64_t start = 0;
    uint64_t end = 0;

    for (uint64_t ii = 0; ii < num_jobs; ii++) {
        if ( iterations > block_count ) {
            end = start + block_count;
        } else {
            end = iterations;
        }
        Job_Manager::register_job(job_handle, [this, start, end]() {
            for (uint64_t jj = start; jj < end; jj++ ) {
                Execute(jj);
            }
        });
        start = end;
    }

    return job_handle;
}

} // end namespace core

#endif //__JOB_H__
