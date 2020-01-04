#ifndef __MESH_LOADER_H__
#define __MESH_LOADER_H__

#include <string>
#include "engine_core.h"

class Mesh_Loader {
public:
     virtual void init( void ) {};
     virtual void load( std::string file_path ) {};
     virtual void shutdown( void ) {};
};

#endif //__MESH_LOADER_H__
