#include <vector>
#include "mesh.h"
#include "../math/math_utils.h"
#include "platform/platform.h"

namespace core {

Mesh::Mesh() {
    indices_count = 0;
    indices = NULL;
    vertices_count = 0;
    vertices = NULL;
    normals_count = 0;
    normals = NULL;
    textures_count = 0;
    textures = NULL;
    vao = NULL;
}

UhRC_t Mesh::serialize( std::ofstream* out_stream )
{
    // serialize indices
    out_stream->write((char*)&this->indices_count, sizeof(uint32_t));
    for ( uint32_t i = 0; i < this->indices_count; i++ ) {
        out_stream->write((char*)&indices[i], sizeof(uint32_t));
    }

    // serialize vertices
    out_stream->write((char*)&this->vertices_count, sizeof(uint32_t));
    for ( uint32_t i = 0; i < this->vertices_count; i++ ) {
        out_stream->write((char*)&this->vertices[i], sizeof(float));
    }

    // serialize normals
    out_stream->write((char*)&this->normals_count, sizeof(uint32_t));
    for ( uint32_t i = 0; i < this->normals_count; i++ ) {
        out_stream->write((char*)&this->normals[i], sizeof(float));
    }

    // serialize textures
    out_stream->write((char*)&this->textures_count, sizeof(uint32_t));
    for ( uint32_t i = 0; i < this->textures_count; i++ ) {
        out_stream->write((char*)&this->textures[i], sizeof(float));
    }

    return SUCCESS;
}

UhRC_t Mesh::deserialize( std::ifstream* in_stream )
{
    in_stream->read((char*)&this->indices_count, sizeof(uint32_t));
    this->indices = (uint32_t*)malloc(sizeof(uint32_t) * this->indices_count);
    for ( uint32_t i = 0; i < this->indices_count; i++ ) {
        in_stream->read((char*)&this->indices[i], sizeof(uint32_t));
    }

    in_stream->read((char*)&this->vertices_count, sizeof(uint32_t));
    this->vertices = (float*)malloc(sizeof(float) * this->vertices_count);
    for ( uint32_t i = 0; i < this->vertices_count; i++ ) {
        in_stream->read((char*)&this->vertices[i], sizeof(float));
    }

    in_stream->read((char*)&this->normals_count, sizeof(uint32_t));
    this->normals = (float*)malloc(sizeof(float) * this->normals_count);
    for ( uint32_t i = 0; i < this->normals_count; i++ ) {
        in_stream->read((char*)&this->normals[i], sizeof(float));
    }

    in_stream->read((char*)&this->textures_count, sizeof(uint32_t));
    this->textures = (float*)malloc(sizeof(float) * this->textures_count);
    for ( uint32_t i = 0; i < this->textures_count; i++ ) {
        in_stream->read((char*)&this->textures[i], sizeof(float));
    }

    this->vao = new core::vao_t;
    create_vao(this->vao);
    bind_vao(this->vao);
    create_index_buffer(this->vao, (int*)this->indices, (int)this->indices_count, STATIC_DRAW); //TODO: need to get ride of this cast
    create_float_attribute(this->vao, 0, this->vertices, this->vertices_count * sizeof(float), 3, STATIC_DRAW);
    create_float_attribute(this->vao, 1, this->normals, this->normals_count * sizeof(float), 3, STATIC_DRAW);
    create_float_attribute(this->vao, 2, this->textures, this->textures_count * sizeof(float), 2, STATIC_DRAW);
    unbind_vao();

    return SUCCESS;
}

void Mesh::generate_flat_plane( Mesh* mesh, Vector3f position, uint32_t width, uint32_t height, float vert_scale )
{
    //TODO: need to add checking to make sure this math does not return floats
    int num_width_squares = (int)(width/vert_scale);
    int num_height_squares = (int)(height/vert_scale);

    int num_height_verts = num_height_squares + 1;
    int num_width_verts = num_width_squares + 1;

    mesh->vertices_count = num_height_verts * num_width_verts * 3;
    mesh->indices_count = 6 * num_width_squares * num_height_squares;
    mesh->vertices = (float*)malloc(sizeof(float) * mesh->vertices_count); //TODO: need to get ride of these malloc calls
    mesh->normals = (float*)malloc(sizeof(float) * mesh->vertices_count);
    mesh->indices = (uint32_t*)malloc(sizeof(uint32_t) * mesh->indices_count);

    int vert_index = 0;
    float x = position.vec.x;
    float y = position.vec.y;
    float z = position.vec.z;
    for ( int i = 0; i < num_width_verts; i++ ) {
        for ( int j = 0; j < num_height_verts; j++ ) {
            mesh->vertices[vert_index * 3] = x;
            mesh->vertices[vert_index * 3 + 1] = y;
            mesh->vertices[vert_index * 3 + 2] = z;
            mesh->normals[vert_index * 3] = 0;
            mesh->normals[vert_index * 3 + 1] = 1;
            mesh->normals[vert_index * 3 + 2] = 0;
            z += vert_scale;
            vert_index++;
        }
        z = position.vec.z;
        x += vert_scale;
    }
    int indices_index = 0;
    int indices_offset = 0;
    for ( int i = 0; i < num_width_squares; i++ ) {
        for ( int j = 0; j < num_height_squares; j++ ) {
            mesh->indices[indices_index] = j + indices_offset;
            mesh->indices[indices_index + 2] = j + num_height_verts + indices_offset;
            mesh->indices[indices_index + 1] = j + num_height_verts + 1 + indices_offset;

            mesh->indices[indices_index + 3] = j + indices_offset;
            mesh->indices[indices_index + 5] = j + num_height_verts + 1 + indices_offset;
            mesh->indices[indices_index + 4] = j + 1 + indices_offset;
            indices_index += 6;
        }
        indices_offset += num_height_verts;
    }
}

void Mesh::generate_face_normals( Mesh* mesh, uint32_t width, uint32_t height, float vert_scale, std::vector<mesh_face_t>* face_normals )
{
    //TODO: need to add checking to make sure this math does not return floats
    int width_box = (int)(width/vert_scale);
    int height_box = (int)(height/vert_scale);

    int height_verts = height_box + 1;
    int width_verts = width_box + 1;

    face_normals->resize(height_verts * width_verts); //TODO: need to fix this scaling generating space for every "box" when not needed
    int face_offset = 0;
    Vector3f v0;
    Vector3f v1;
    Vector3f v2;
    for ( int i = 0; i < width_box; i++ ) {
        for ( int j = 0; j < height_box; j++ ) {
            //top face
            v0.vec.x = mesh->vertices[(j + face_offset) * 3];
            v0.vec.y = mesh->vertices[(j + face_offset) * 3 + 1];
            v0.vec.z = mesh->vertices[(j + face_offset) * 3 + 2];
            v1.vec.x = mesh->vertices[(j + face_offset + height_verts + 1) * 3];
            v1.vec.y = mesh->vertices[(j + face_offset + height_verts + 1) * 3 + 1];
            v1.vec.z = mesh->vertices[(j + face_offset + height_verts + 1) * 3 + 2];
            v2.vec.x = mesh->vertices[(j + face_offset + 1) * 3];
            v2.vec.y = mesh->vertices[(j + face_offset + 1) * 3 + 1];
            v2.vec.z = mesh->vertices[(j + face_offset + 1) * 3 + 2];
            face_normals->at(j + face_offset).top_face = generate_face_norm(v0, v1, v2);
            //bottom face
            v1.vec.x = mesh->vertices[(j + face_offset + height_verts) * 3];
            v1.vec.y = mesh->vertices[(j + face_offset + height_verts) * 3 + 1];
            v1.vec.z = mesh->vertices[(j + face_offset + height_verts) * 3 + 2];
            v2.vec.x = mesh->vertices[(j + face_offset + height_verts + 1) * 3];
            v2.vec.y = mesh->vertices[(j + face_offset + height_verts + 1) * 3 + 1];
            v2.vec.z = mesh->vertices[(j + face_offset + height_verts + 1) * 3 + 2];
            face_normals->at(j + face_offset).bottom_face = generate_face_norm(v0, v1, v2);
        }
        face_offset += height_verts;
    }
}

void Mesh::generate_and_set_vert_normals( Mesh* mesh, uint32_t width, uint32_t height, float vert_scale, std::vector<mesh_face_t>* face_normals )
{

    int width_box = (int)(width/vert_scale);
    int height_box = (int)(height/vert_scale);

    int height_verts = height_box + 1;
    int width_verts = width_box + 1;

    int vert_max = (height_verts * width_verts) - 1;
    int vert_index = 0;
    int end_vert = 0;
    int start_vert = 0;
    for ( int i = 0; i < width_verts; i++ ) {
        end_vert = ((i+1)*(height_box+1) - 1);
        start_vert = vert_index;
        for ( int j = 0; j < height_verts; j++ ) {
            Vector3f vert_normal(0, 0, 0);
            if ( (vert_index + (height_verts + 1)) <= vert_max && vert_index != end_vert ) {
                vert_normal = vert_normal + face_normals->at(vert_index).top_face;
                vert_normal = vert_normal + face_normals->at(vert_index).bottom_face;
            }
            if ( (vert_index - height_verts) >= 0 && (vert_index - height_verts) != (end_vert - height_verts) ) {
                vert_normal = vert_normal + face_normals->at(vert_index-height_verts).bottom_face;
            }
            if ( (vert_index - (height_verts + 1)) >= 0 && vert_index != start_vert ) {
                vert_normal = vert_normal + face_normals->at(vert_index - (height_verts + 1)).top_face;
                vert_normal = vert_normal + face_normals->at(vert_index - (height_verts + 1)).bottom_face;
            }
            if ( (vert_index - 1) >= 0 && (vert_index - 1) >= start_vert ) {
                vert_normal = vert_normal + face_normals->at(vert_index - 1).top_face;
            }
            vert_normal = vert_normal.normalize();
            mesh->normals[vert_index * 3] = vert_normal.vec.x;
            mesh->normals[vert_index * 3 + 1] = vert_normal.vec.y;
            mesh->normals[vert_index * 3 + 2] = vert_normal.vec.z;
            vert_index++;
        }
    }
}

float Mesh::generate_height( float x, float y, Image* height_map )
{
    float final_height = 0;
    int x_bl;
    int y_bl;
    int x_tl;
    int y_tl;
    int x_br;
    int y_br;
    int x_tr;
    int y_tr;
    float bl_height;
    float tl_height;
    float br_height;
    float tr_height;

    // both x and y are whole numbers
    if ( (x == (int)x) && (y == (int)y) ) {
        pixel_data_t pixel_data;
        pixel_data = height_map->get_RGB((int)x, (int)y);
        final_height = (float)(pixel_data.r);
    } else {

        x_bl = (int)x;
        y_bl = (int)y;
        x_tl = x_bl;
        y_tl = y_bl + 1;
        x_br = x_bl + 1;
        y_br = y_bl;
        x_tr = x_br;
        y_tr = y_br + 1;

        pixel_data_t pixel_data;

        pixel_data = height_map->get_RGB(x_bl, y_bl);
        bl_height = (float)(pixel_data.r);

        pixel_data = height_map->get_RGB(x_tl, y_tl);
        tl_height = (float)(pixel_data.r);

        pixel_data = height_map->get_RGB(x_br, y_br);
        br_height = (float)(pixel_data.r);

        pixel_data = height_map->get_RGB(x_tr, y_tr);
        tr_height = (float)(pixel_data.r);

        float r1 = (((x_br - x) / (x_br - x_bl)) * bl_height) + (((x - x_bl) / (x_br - x_bl)) * br_height);
        float r2 = (((x_br - x) / (x_br - x_bl)) * tl_height) + (((x - x_bl) / (x_br - x_bl)) * tr_height);

        final_height = (((y_tl - y) / (y_tl - y_bl)) * r1) + (((y - y_bl) / (y_tl - y_bl)) * r2);
    }

    return final_height;
}

} //end namespace core
