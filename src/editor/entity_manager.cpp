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
     uint32_t id = Engine::crc32(name.c_str());
     entity_look_up.insert({id, (entity_name_list.size() - 1)});
}

Engine::Entity Entity_Manager::get_entity( size_t selected )
{
     uint32_t id = Engine::crc32(entity_name_list[selected].c_str());

     std::unordered_map<uint32_t, size_t>::const_iterator iter = entity_look_up.find(id);
     if ( iter != entity_look_up.end() ) {
          return entity_handle_list[iter->second];
     }

     return 0;
}

std::vector<std::string>& Entity_Manager::get_entity_name_list( void )
{
     return entity_name_list;
}

