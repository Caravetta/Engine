#ifndef __ENGINE_ASSETS_H__
#define __ENGINE_ASSETS_H__

#include <Engine_Types.h>

#ifdef WINDOWS
    #ifdef ENGINE_EXPORT
        #define ENGINE_API __declspec(dllexport)
    #else
        #define ENGINE_API __declspec(dllimport)
    #endif
#elif LINUX
    #define ENGINE_API __attribute__ ((visibility ("default")))
#else
    #define ENGINE_API
#endif

namespace Engine {

class ENGINE_API Mesh_Asset : public Asset {
public:
    Mesh mesh;

    Mesh_Asset();
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

} // end namespace Engine

#endif
