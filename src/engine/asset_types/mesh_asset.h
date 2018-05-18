#if !defined(MESH_ASSET_H)

#include <string>
#include "../core/core.h"

class Mesh_Asset : public core::Asset {
public:
    core::Mesh mesh;

    Mesh_Asset();
    void load( std::string file_path );
};

#define MESH_ASSET_H
#endif
