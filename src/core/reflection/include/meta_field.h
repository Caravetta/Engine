#ifndef __META_FIELD_H__
#define __META_FIELD_H__

#include "core_common.h"

namespace Engine {

enum Meta_Field_Flags {
     SERIALIZE_FIELD = 1 << 0,
};

struct Meta_Field {
     const char*    __name;
     uint32_t       __name_crc;
     uint32_t       __size;
     uint32_t       __offset;
     uint32_t       __flags;

     Meta_Field( void );
};

} // end namespace Engine

#endif //__META_FIELD_H__
