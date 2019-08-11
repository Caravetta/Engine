#ifndef __COMPONENT_H__
#define __COMPONENT_H__

#include "core_common.h"

namespace Engine {

typedef uint32_t Component_ID;

#define INVALID_COMPONENT 0

#define COMPONENT_DECLARE( _comp )                               \
     public:                                                     \
     static Component_ID                          __id;          \
     static const size_t                          __size;        \
     static Engine::Component_Registrar<_comp>    __s_registrar; \
     static void setup_component( Component_ID id );

#define COMPONENT_DEFINE( _comp )                                          \
     Component_ID                       _comp::__id = INVALID_COMPONENT;   \
     const size_t                       _comp::__size = sizeof(_comp);     \
     Engine::Component_Registrar<_comp> _comp::__s_registrar;              \
     void _comp::setup_component( Component_ID id )                        \
     {                                                                     \
          __id = id;                                                       \
     }

Rc_t init_component_system( void );

template<class T> Component_ID component_id( void );
template<class T> size_t component_size( void );

class Component_Base_Registrar {
public:
     Component_Base_Registrar*          __next;
     static Component_Base_Registrar*   __s_head;
     static Component_Base_Registrar*   __s_tail;

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

} // end namespace Engine

#include "component.inl"

#endif //__COMPONENT_H__
