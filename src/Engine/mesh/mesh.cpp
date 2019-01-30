#include <vector>
#include <fstream>
#include "Engine.h"
#include "platform.h"

namespace Engine {

Mesh::Mesh() {
    indices_count = 0;
    indices = NULL;
    vertices_count = 0;
    vertices = NULL;
    normals_count = 0;
    normals = NULL;
    textures_count = 0;
    textures = NULL;
    //vao = NULL;
}

Rc_t Mesh::serialize( std::ofstream* out_stream )
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

Rc_t Mesh::deserialize( std::ifstream* in_stream )
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
#if 0
    this->vao = new core::vao_t;
    create_vao(this->vao);
    bind_vao(this->vao);
    create_index_buffer(this->vao, (int*)this->indices, (int)this->indices_count, STATIC_DRAW); //TODO: need to get ride of this cast
    create_float_attribute(this->vao, 0, this->vertices, this->vertices_count * sizeof(float), 3, 3 * sizeof(float), 0, STATIC_DRAW);
    create_float_attribute(this->vao, 1, this->normals, this->normals_count * sizeof(float), 3, 3 * sizeof(float), 0, STATIC_DRAW);
    create_float_attribute(this->vao, 2, this->textures, this->textures_count * sizeof(float), 2, 2 * sizeof(float), 0, STATIC_DRAW);
    unbind_vao();
#endif
    return SUCCESS;
}

} //end namespace Engine
