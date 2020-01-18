#ifndef __ASSIMP_MESH_LOADER_H__
#define __ASSIMP_MESH_LOADER_H__

#include <string>
#include "mesh_loader.h"
#include "engine_core.h"

class Assimp_Mesh_Loader : public Mesh_Loader {
public:
     void init( void );
     void load( std::string file_path );
     void shutdown( void );

private:
     bool is_initialized;
};

#endif //__ASSIMP_MESH_LOADER_H__
