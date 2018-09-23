#if !defined(HANDLE_H)

namespace core {

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

#define HANDLE_H
#endif
