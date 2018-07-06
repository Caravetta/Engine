#if !defined(MESH_H)

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
        vao* vao;

        Mesh();

        UhRC_t serialize( std::ofstream* out_stream );
        UhRC_t deserialize( std::ifstream* in_stream );

        /**
            Generates a flat mesh plane starting at the given position.

            @param mesh pointer to the perallocated memory for storing the generated mesh
            @param position the starting position of the mesh (lower left corner of generated mesh)
            @param width the width to generate the mesh to
            @param height the height/depth to generate the mesh to
            @param vert_scale the space between each vertice
            @return nothing //TODO: change this to a return code

        */
        static void generate_flat_plane( Mesh* mesh, Vector3f position, uint32_t width, uint32_t height, float vert_scale );

        /**
            Generates face normals for the given mesh

            @param mesh pointer to the mesh the generate the face normals for
            @param width the width of the mesh
            @param height the height/depth of the mesh
            @param vert_scale the space between each vertice
            @param face_normals a pointer to a vector of mesh_face_t that will hold the generated face normals
            @return nothing //TODO: change this to a return code
        */
        static void generate_face_normals( Mesh* mesh, uint32_t width, uint32_t height, float vert_scale, std::vector<mesh_face_t>* face_normals );


        /**
            Generates vertex normals for the given mesh from the supplied face normals

            @param mesh pointer to the mesh that will have its normals set
            @param width the width of the mesh
            @param height the height/depth of the mesh
            @param vert_scale the space between each vertice
            @param face_normals a pointer to a vector of mesh_face_t that will be used to calculate the normals
            @return nothing //TODO: change this to a return code
        */
        static void generate_and_set_vert_normals( Mesh* mesh, uint32_t width, uint32_t height, float vert_scale, std::vector<mesh_face_t>* face_normals );

    private:
        static float generate_height( float x, float y, Image* height_map );
    };

} //end namespace core

#define MESH_H
#endif
