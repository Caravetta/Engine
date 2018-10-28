#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "../core_common.h"

#define COMPONENT(name,...)         \
                                    \
    typedef struct                  \
    {                               \
        __VA_ARGS__                 \
    } name;

#endif //__COMPONENT_H__
