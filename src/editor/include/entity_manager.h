#ifndef __ENTITY_MANAGER_H__
#define __ENTITY_MANAGER_H__

#include <vector>
#include <string>
#include "engine_core.h"

class Entity_Manager {
private:
     std::vector<std::string> entity_name_list;
     std::vector<Engine::Entity> entity_handle_list;

public:
     Entity_Manager( void );
     ~Entity_Manager( void );

     void create_entity( void );
     Engine::Entity get_entity( std::string entity_name );
     std::vector<std::string>& get_entity_name_list( void );

};

#endif //__ENTITY_MANAGER_H__
