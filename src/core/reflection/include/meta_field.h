#ifndef __META_FIELD_H__
#define __META_FIELD_H__

#include "core_common.h"
#include "vector3f.h"
#include "color.h"

namespace Engine {

enum Meta_Field_Flags {
     SERIALIZE_FIELD = 1 << 0,
};

enum Meta_Field_Type {
     META_TYPE_VECTOR3F,
     META_TYPE_FLOAT,
     META_TYPE_U64,
     META_TYPE_U32,
     META_TYPE_COLOR,
     META_TYPE_NON_BASE,
};

struct Meta_Field {
     const char*         __name;
     uint32_t            __name_crc;
     uint32_t            __size;
     uint32_t            __offset;
     uint32_t            __flags;
     Meta_Field_Type     type;

     Meta_Field( void );

     template<class T> Meta_Field_Type get_field_type( void );
};

// built in types for the engine
template<> Meta_Field_Type Meta_Field::get_field_type<Engine::Vector3f>( void );
template<> Meta_Field_Type Meta_Field::get_field_type<Engine::Color>( void );
template<> Meta_Field_Type Meta_Field::get_field_type<float>( void );
template<> Meta_Field_Type Meta_Field::get_field_type<uint64_t>( void );
template<> Meta_Field_Type Meta_Field::get_field_type<uint32_t>( void );

} // end namespace Engine

#include "meta_field.inl"

#endif //__META_FIELD_H__
