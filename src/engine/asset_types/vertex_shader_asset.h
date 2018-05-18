#if !defined(VERTEX_SHADER_ASSET_H)

#include "../core/core.h"

class Vertex_Shader_Asset : public core::Asset {
public:
    unsigned int vertex_id;

    Vertex_Shader_Asset();
    void load( std::string file_path );

};

#define VERTEX_SHADER_ASSET_H
#endif
