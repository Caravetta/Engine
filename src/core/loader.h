#if !defined(UNHINGED_LOADER_H)

#include <vector>
#include <string.h>
#include <stdio.h>
#include <fstream>
#include "core_common.h"
#include "mesh/mesh.h"
#include "texture/texture.h"
#include "image/image.h"

namespace core {

    typedef enum {
        OBJ_FILE,
        TGA_FILE,
    } file_type_t;

    CORE_API Mesh* load_model( std::string file_path, file_type_t model_type );
    CORE_API Texture* load_texture( std::string file_path, file_type_t texture_type );

    void load_obj_file( std::string file_path, Mesh* mesh );

} //end namespace core

#define UNHINGED_LOADER_H
#endif
