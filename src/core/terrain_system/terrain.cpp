#include "terrain.h"
#include "../math/fractal_noise.h"

namespace core {

Terrain::Terrain( Vector3f position, uint32_t width, uint32_t height, float vert_space,
                  double frequency, int octaves, int x_scale, int z_scale, uint32_t patch_width,
                  uint32_t patch_height )
{
    this->total_width = width;
    this->total_height = height;
    this->position = position;

    generate_patches( frequency, octaves, x_scale, z_scale, patch_width, patch_height );
}

void Terrain::generate_patches( double frequency, int octaves, int x_scale, int z_scale,
                                uint32_t patch_width, uint32_t patch_height )
{
    if ( total_width < patch_width ) {
        return; //TODO: need to add a return code to handle errors
    }
    uint32_t num_width_patches = total_width / patch_width;

    if ( total_height < patch_height ) {
        return;
    }
    uint32_t num_height_patches = total_height / patch_height;

    uint32_t total_num_patches = num_width_patches * num_height_patches;

    LOG("total_num_patches:" << total_num_patches << " num_height_patches:" << num_height_patches << " num_width_patches:" << num_width_patches);
    patches.resize(total_num_patches);



    FractalNoise fractal_noise;
    fractal_noise.setBaseFrequency((float)frequency);
    fractal_noise.setOctaves(octaves);
    uint32_t mesh_offset = 0;
    for ( uint32_t i = 0; i < num_height_patches; i++ ) {
        for ( uint32_t j = 0; j < num_width_patches; j++ ) {
            Vector3f cur_patch_pos(position.x + (j * patch_width),
                                   position.y,
                                   position.z + (i * patch_height));
            patches[mesh_offset].position = cur_patch_pos;
            generate_patch(&patches[mesh_offset].mesh, cur_patch_pos, patch_width, patch_height, x_scale, z_scale, &fractal_noise);
            mesh_offset++;
        }
    }
}

void Terrain::generate_patch( Mesh* mesh, Vector3f patch_position, uint32_t patch_width, uint32_t patch_height, int x_scale, int z_scale, FractalNoise* fractal_noise )
{
    Mesh::generate_flat_plane(mesh, patch_position, patch_width, patch_height, 1);

    int height_verts = patch_height + 1;
    int width_verts = patch_width + 1;

    int vert_index = 0;
    float y;
    for ( int i = 0; i < width_verts; i++ ) {
        for ( int j = 0; j < height_verts; j++ ) {
            y = fractal_noise->noise(mesh->vertices[vert_index * 3]*(1.0f/x_scale), mesh->vertices[vert_index * 3 + 2]*(1.0f/z_scale), 0);
            y = scale_float(y, -1.0f, 1.0f, -500.0f, 500.0f);
            mesh->vertices[vert_index * 3 + 1] = y;
            vert_index++;
        }
    }
    //calculate face normals
    std::vector<mesh_face_t> mesh_face_vector;
    Mesh::generate_face_normals(mesh, patch_width, patch_height, 1, &mesh_face_vector);

    //calculate and set vert normals
    Mesh::generate_and_set_vert_normals(mesh, patch_width, patch_height, 1, &mesh_face_vector); //TODO: need to fix the normal generation
}

} //end namespace core
