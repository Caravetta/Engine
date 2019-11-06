#include "meta_field.h"
#include "vector3f.h"

namespace Engine {

Meta_Field::Meta_Field( void )
{
     __name_crc = __size = __offset = 0;
     __flags = 0;
}

template<>
Meta_Field_Type Meta_Field::get_field_type<float>( void )
{
     return META_TYPE_FLOAT;
}

template<>
Meta_Field_Type Meta_Field::get_field_type<Engine::Vector3f>( void )
{
     return META_TYPE_VECTOR3F;
}

template<>
Meta_Field_Type Meta_Field::get_field_type<uint64_t>( void )
{
     return META_TYPE_U64;
}

template<>
Meta_Field_Type Meta_Field::get_field_type<uint32_t>( void )
{
     return META_TYPE_U32;
}

} // end namespace Engine

