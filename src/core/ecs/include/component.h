#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include <vector>
#include "core_common.h"

namespace Engine {

typedef uint32_t Component_ID;
typedef void (*comp_mem_init_func)( uint8_t* mem );
typedef void (*comp_mem_cpy_func)( uint8_t* source, uint8_t* dest );

#define INVALID_COMPONENT 0

#define COMPONENT_DECLARE( _comp )                                    \
     public:                                                          \
     static Engine::Component_ID                  __id;               \
     static const size_t                          __size;             \
     static const char*                           __name;             \
     static Engine::Component_Registrar<_comp>    __s_comp_registrar; \
     static void setup_component( Engine::Component_ID id );          \
     static void mem_init( uint8_t* mem ) {new (mem) _comp;}          \
     static void mem_cpy( uint8_t* source, uint8_t* dest )            \
     {                                                                \
          _comp* p_source = (_comp*)source;                           \
          _comp* p_dest = (_comp*)dest;                               \
          *p_dest = *p_source;                                        \
     }


#define COMPONENT_DEFINE( _comp )                                                    \
     Engine::Component_ID               _comp::__id = INVALID_COMPONENT;             \
     const size_t                       _comp::__size = sizeof(_comp);               \
     const char*                        _comp::__name = #_comp;                      \
     Engine::Component_Registrar<_comp> _comp::__s_comp_registrar;                   \
     void _comp::setup_component( Engine::Component_ID id )                          \
     {                                                                               \
          __id = id;                                                                 \
          Engine::add_component_info(__id, __size, _comp::mem_init, _comp::mem_cpy); \
     }

Rc_t init_component_system( void );

void add_component_info( Component_ID id, size_t size, comp_mem_init_func mem_init, comp_mem_cpy_func mem_cpy );

template<class T> Component_ID component_id( void );
template<class T> size_t component_size( void );
comp_mem_init_func component_mem_init( Component_ID id );
comp_mem_cpy_func component_mem_cpy( Component_ID id );
size_t component_size( Component_ID id );
std::vector<Component_ID> get_component_list( void );
const char* get_component_name( Component_ID id );

class Component_Base_Registrar {
public:
     Component_Base_Registrar*          __next;
     static Component_Base_Registrar*   __s_head;
     static Component_Base_Registrar*   __s_tail;
     static std::vector<Component_ID>   __component_list;
     static std::vector<const char*>    __component_names;

     Component_Base_Registrar( void );
     ~Component_Base_Registrar( void );

     virtual void component_register( Component_ID id ) = 0;

     static void add_to_list( Component_Base_Registrar* registrar );
     static void register_components( void );
};

template<class T>
class Component_Registrar : public Component_Base_Registrar {
public:
     Component_Registrar( void );
     ~Component_Registrar( void );

     virtual void component_register( Component_ID id );
};

namespace COMP_SYS {
struct comp_test {
     const static uint32_t id = 10;
};

}
struct comp_test {
     const static uint32_t id = 11;
};

} // end namespace Engine

#include "component.inl"

#endif //__COMPONENT_H__
