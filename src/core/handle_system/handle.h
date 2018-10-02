#ifndef __HANDLE_H__
#define __HANDLE_H__

namespace core {

#define HANDLE_SET_ACTIVE 1
#define HANDLE_SET_NON_ACTIVE 0

typedef struct {
    union {
        struct {
            uint64_t index  : 32;
            uint64_t phase  : 31;
            uint64_t active : 1;
        };
        uint64_t id;
    };
} base_handle_t;

} // end namespace core

#endif //__HANDLE_H__
