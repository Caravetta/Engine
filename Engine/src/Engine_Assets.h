#ifndef __ENGINE_ASSETS_H__
#define __ENGINE_ASSETS_H__

#include <Engine_Types.h>

namespace Engine {

class ENGINE_API Mesh_Asset : public Asset {
public:
    Mesh mesh;

    Mesh_Asset();
    void load( std::string file_path );
};

class ENGINE_API Texture_Asset : public Asset {
public:
    Texture texture;

    Texture_Asset();
    void load( std::string file_path );
};

class ENGINE_API Vertex_Shader_Asset : public Asset {
public:
    unsigned int id;

    Vertex_Shader_Asset();
    void load( std::string file_path );

};

class ENGINE_API Fragment_Shader_Asset : public Asset {
public:
    unsigned int id;

    Fragment_Shader_Asset();
    void load( std::string file_path );

};

class ENGINE_API Font_Asset : public Asset {
public:
    Font_Handle handle;

    Font_Asset();
    void load( std::string file_path );

};

} // end namespace Engine

#endif
