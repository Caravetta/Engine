#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <vector>
#include <string>
#include <unordered_map>
#include "engine_core.h"

class Entity_Manager {
private:
     std::vector<std::string> entity_name_list;
     std::vector<Engine::Entity> entity_handle_list;
     std::unordered_map<uint32_t, size_t> entity_look_up;

public:
     Entity_Manager( void );
     ~Entity_Manager( void );

     void create_entity( void );
     Engine::Entity get_entity( size_t selected );
     std::vector<std::string>& get_entity_name_list( void );
     std::string* entity_name( size_t selected );
     void update_entity_name( size_t selected, char* new_name );

};

#endif //__ENTITY_MANAGER_H__
