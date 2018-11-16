#ifndef __MESH_H__
#define __MESH_H__

#include "../core_common.h"
#include "../platform/platform.h"
#include "../image/image.h"
#include "../math/vector.h"
#include "../math/fractal_noise.h"

namespace core {

typedef struct {
    Vector3f top_face;
    Vector3f bottom_face;
} mesh_face_t;

typedef struct {
    uint32_t indices_count;
    uint32_t* indices;
    uint32_t vertices_count;
    float* vertices;
    uint32_t normals_count;
    float* normals;
    uint32_t textures_count;
    float* textures;
} mesh_data_t;

class CORE_API Mesh {
public:
    uint32_t indices_count;
    uint32_t* indices;
    uint32_t vertices_count;
    float* vertices;
    uint32_t normals_count;
    float* normals;
    uint32_t textures_count;
    float* textures;
    vao_t* vao;

    Mesh();

    UhRC_t serialize( std::ofstream* out_stream );
    UhRC_t deserialize( std::ifstream* in_stream );
};

class CORE_API Instanced_Mesh : public Mesh {

    void update_transformation_matrix();
};

} //end namespace core

#endif //__MESH_H__
