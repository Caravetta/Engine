#if !defined(FRAGMENT_SHADER_ASSET_H)

#include "../core/core.h"

class Fragment_Shader_Asset : public core::Asset {
public:
    unsigned int fragment_id;

    Fragment_Shader_Asset();
    void load( std::string file_path );

};

#define FRAGMENT_SHADER_ASSET_H
#endif
