#ifndef __RETURN_CODES_H__
#define __RETURN_CODES_H__

enum Rc_t {
    SUCCESS             = 0,
    ENGINE_ERROR        = -1000,
    INDEX_BOUNDS_ERROR,
    INVALID_SIZE_ERROR,
};

#endif // __RETURN_CODES_H__

