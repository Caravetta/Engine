#ifndef __ARCHETYPE_H__
#define __ARCHETYPE_H__

#include <unordered_map>
#include <vector>
#include "core_common.h"
#include "component.h"

namespace Engine {

enum Archetype_Usage {
     ARCHETYPE_COMPONENT,
     ARCHETYPE_SHARED,
     ARCHETYPE_TAG,
};

struct Archetype_Comp_Info {
     Component_ID id;
     Archetype_Usage usage;
};

class ENGINE_API Archetype {
private:
     std::unordered_map<Component_ID, uint64_t>   __component_id_map;
     std::vector<Archetype_Comp_Info>             __component_info_vec;
     size_t                                       __total_shared_comp_size;
     size_t                                       __total_comp_size;

public:
     Archetype( void );
     template<typename T> Rc_t add_component( void );
     template<typename T> Rc_t add_shared_component( void );
     template<typename T> Rc_t add_tag( void );
     size_t get_total_shared_comp_size( void );
     size_t get_total_comp_size( void );
     size_t get_arhcetype_size( void );
     void add_component( Component_ID id, Archetype_Usage usage );
     std::vector<Archetype_Comp_Info>& get_component_info_vec( void );
};

template<typename T>
Rc_t add_component( void )
{

}

template<typename T>
Rc_t add_shared_component( void )
{

}

template<typename T>
Rc_t add_tag( void )
{

}

} // end namespace Engine

#endif //__ARCHETYPE_H__
