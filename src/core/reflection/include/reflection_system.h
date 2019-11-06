#ifndef __REFLECTION_SYSTEM_H__
#define __REFLECTION_SYSTEM_H__

#include "core_common.h"
#include "meta_base.h"
#include "meta_info.h"
//#include "meta_struct.h"

namespace Engine {

class Meta_Struct;

namespace Reflection {


Rc_t init_reflection_system( void );

bool register_type( Meta_Base* type );

Meta_Struct* get_meta_struct( const char* name );
Meta_Info* get_meta_info( const char* name );

} // end namespace Reflection
} // end namespace Engine

#include "reflection_system.inl"

#endif //__REFLECTION_SYSTEM_H__
