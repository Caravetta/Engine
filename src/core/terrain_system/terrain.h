#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include "../core_common.h"
#include "../math/vector.h"
#include "../mesh/mesh.h"

namespace core {

    class CORE_API Terrain {
        public:

        struct patch_t {
            Vector3f position;
            Mesh     mesh;
            uint32_t width;
            uint32_t height;
        };

        std::vector<patch_t> patches;
        uint32_t total_width;
        uint32_t total_height;
        float vert_space;
        Vector3f position;

        Terrain( Vector3f position, uint32_t width, uint32_t height, float vert_space,
                double frequency, int octaves, int x_scale, int z_scale, uint32_t patch_width,
                uint32_t patch_height );

        private:
        void generate_patches( double frequency, int octaves, int x_scale, int z_scale, uint32_t patch_width, uint32_t patch_height );
        void generate_patch( Mesh* mesh, Vector3f patch_position, uint32_t patch_width, uint32_t patch_height, int x_scale, int z_scale, FractalNoise* fractal_noise );
    };

} //end namespace core

#endif //__TERRAIN_H__
