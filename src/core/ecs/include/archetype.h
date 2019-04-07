#ifndef __ARCHETYPE_H__
#define __ARCHETYPE_H__

#include <vector>
#include <unordered_map>
#include "return_codes.h"

namespace Engine {

struct ENGINE_API Archetype {
public:
    std::unordered_map<uint32_t, uint64_t> id_map;
    std::vector<uint32_t> used_ids;

public:
    Archetype( void );
    Rc_t add_component( const uint32_t id );
    Rc_t add_tag( const uint32_t id );
    bool has_component( const uint32_t id );
    bool has_tag( const uint32_t id );
    template<typename T> Rc_t add_component( void );
    template<typename T> Rc_t add_tag( void );
    template<typename T> bool has_component( void );
    template<typename T> bool has_tag( void );
};

template<typename T>
Rc_t add_component( void )
{

}

template<typename T>
Rc_t add_tag( void )
{

}

template<typename T>
bool has_component( void )
{

}

template<typename T>
bool has_tag( void )
{

}

} // end namespace Engine

#endif // __ARCHETYPE_H__
