#include "editor_context.h"

Editor_Context* Editor_Context::instance = NULL;

Editor_Context::Editor_Context( void )
{
     entity_selected = false;
     selected_entity = 1000000;
     scene_texture = 0;
}

Editor_Context* Editor_Context::get_instance( void )
{
     if ( instance == NULL ) {
          instance = new (std::nothrow) Editor_Context;
     }

     return instance;
}

