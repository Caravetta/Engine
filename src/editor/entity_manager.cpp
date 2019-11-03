#include "entity_manager.h"

Entity_Manager::Entity_Manager( void )
{
     // do nothing
}

Entity_Manager::~Entity_Manager( void )
{
     // do nothing
}

void Entity_Manager::create_entity( void )
{
     entity_handle_list.push_back(Engine::create_entity());
     std::string name = "Entity_" + std::to_string(entity_handle_list.size());
     entity_name_list.push_back(name);
}

Engine::Entity Entity_Manager::get_entity( std::string entity_name )
{
     return 0;
}

std::vector<std::string>& Entity_Manager::get_entity_name_list( void )
{
     return entity_name_list;
}

