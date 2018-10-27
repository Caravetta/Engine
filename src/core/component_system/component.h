#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "../core_common.h"

#define COMPONENT(name,...)         \
                                    \
    typedef struct                  \
    {                               \
        union                       \
        {                           \
            struct core::Component; \
            core::Component parent; \
        };                          \
        __VA_ARGS__                 \
    } name;

namespace core {

    struct CORE_API Component {
    public:
        //Component(){};
    };

} // end namespace core

#endif //__COMPONENT_H__
