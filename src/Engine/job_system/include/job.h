#ifndef __JOB_H__
#define __JOB_H__

#include <functional>
#include "core_common.h"
#include "job_manager.h"

namespace Engine {

struct Job_Loop {
private:
    uint64_t _iteration_count;
    uint64_t _block_count;
public:
    Job_Handle Schedule( uint64_t iterations, uint64_t block_count );
    virtual void Execute( uint64_t index ) = 0;
};

} // end namespace Engine

#endif //__JOB_H__
