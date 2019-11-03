#ifndef __RETURN_CODES_H__
#define __RETURN_CODES_H__

namespace Engine {

enum Rc_t {
     SUCCESS             = 0,
     ENGINE_ERROR        = -1000,
     INDEX_BOUNDS_ERROR,
     INVALID_SIZE_ERROR,
     MEMORY_ALLOC_FAILED,
     INVALID_ENTITY,
     NOT_VALID_COMPONENT,
     ARCHETYPE_ALREADY_EXISTS,
     OSTREAM_ERROR,
     INVALID_META_PROPERTY,
};

} // end namespace Engine

#endif // __RETURN_CODES_H__

