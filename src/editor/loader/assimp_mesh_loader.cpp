#include "assimp_mesh_loader.h"
#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "mesh_loader.h"
#include "editor_context.h"

#define ASSIMP_IMPORT_FLAGS aiProcess_CalcTangentSpace      | \
                            aiProcess_Triangulate           | \
                            aiProcess_SortByPType           | \
                            aiProcess_GenNormals            | \
                            aiProcess_GenUVCoords           | \
                            aiProcess_OptimizeMeshes        | \
                            aiProcess_ValidateDataStructure

typedef aiScene* (*assimp_import_from_file_proc) ( const char* pFile, unsigned int pFlags );
typedef aiScene* (*assimp_import_from_memory_proc) ( const char* pBuffer, unsigned int pLength, unsigned int pFlags, const char* pHint );
typedef void (*assimp_release_import_proc) ( aiScene* p_scene );

assimp_import_from_file_proc       assimp_import_from_file  = NULL;
assimp_import_from_memory_proc     assimp_import_from_memory = NULL;
assimp_release_import_proc         assimp_release_import = NULL;

static Engine::Rc_t _load_assimp_lib( void )
{
	LIB_HANDLE handle;

	LOAD_LIB("./libassimp");

	if ( assimp_import_from_file == NULL ) {
		LOAD_LIB_FUNC_STRING(assimp_import_from_file, "aiImportFile");
	}

	if ( assimp_import_from_memory == NULL ) {
     	LOAD_LIB_FUNC_STRING(assimp_import_from_memory, "aiImportFileFromMemory");
	}

	if ( assimp_release_import == NULL ) {
     	LOAD_LIB_FUNC_STRING(assimp_release_import, "aiReleaseImport");
	}

	return Engine::SUCCESS;
}

void Assimp_Mesh_Loader::init( void )
{
	Engine::Rc_t rc = _load_assimp_lib();
	if ( rc != Engine::SUCCESS ) {
		is_initialized = false;
		LOG_ERROR("%s: Failed to init Assimp Mesh Loader", __FUNCTION__);
	} else {
		is_initialized = true;
	}
}

void Assimp_Mesh_Loader::load( std::string file_path )
{
     if ( is_initialized == false ) {
           LOG_ERROR("%s: Failed to load %s Assimp_Mesh_Loader not initialized", __FUNCTION__, file_path.c_str());
           return;
     }

     aiScene* scene = NULL;
     aiMesh* mesh = NULL;

     scene = assimp_import_from_file(file_path.c_str(), ASSIMP_IMPORT_FLAGS);
     if ( scene == NULL ) {
          LOG_ERROR("%s: Failed to load mesh data", __FUNCTION__);
          return;
     }

     LOG("Num Meshes %" PRIu64 "", (uint64_t)scene->mNumMeshes);
	for ( uint64_t ii = 0; ii < (uint64_t)scene->mNumMeshes; ii++ ) {
     	mesh = scene->mMeshes[ii];
          LOG("Mesh %s", mesh->mName.data);
          LOG("Num Verts %" PRIu64 "", (uint64_t)mesh->mNumVertices);
          LOG("Num Index %" PRIu64 "", (uint64_t)(mesh->mNumFaces * 3));
          if ( mesh->mNormals != NULL ) {
               LOG("Has Normals");
          }
          if ( mesh->mTextureCoords != NULL ) {
               LOG("Has TextCords");
          }
     }

     Editor_Context& context = *Editor_Context::get_instance();

     for ( uint64_t ii = 0; ii < (uint64_t)scene->mNumMeshes; ii++ ) {
          Engine::Mesh_Data mesh_data;

          mesh = scene->mMeshes[ii];

          mesh_data.positions.resize((uint64_t)(mesh->mNumVertices * 3));
          mesh_data.indices.resize((uint64_t)(mesh->mNumFaces * 3));

          uint64_t vert_idx = 0;
          //grab vert data
          for ( uint64_t ii = 0; ii < (uint64_t)mesh->mNumVertices; ii++ ) {
               mesh_data.positions[vert_idx++] = mesh->mVertices[ii].x;
               mesh_data.positions[vert_idx++] = mesh->mVertices[ii].y;
               mesh_data.positions[vert_idx++] = mesh->mVertices[ii].z;
          }

          uint64_t indice_idx = 0;
          //grab indices
          for ( uint64_t ii = 0; ii < (uint64_t)mesh->mNumFaces; ii++ ) {
               mesh_data.indices[indice_idx++] = mesh->mFaces[ii].mIndices[0];
               mesh_data.indices[indice_idx++] = mesh->mFaces[ii].mIndices[1];
               mesh_data.indices[indice_idx++] = mesh->mFaces[ii].mIndices[2];
          }

          Engine::load_mesh(Engine::STATIC_MESH, mesh->mName.data, mesh_data);
          Engine::Mesh_Handle mesh_handle = Engine::mesh_handle(mesh->mName.data);
          context.mesh_map.insert({mesh->mName.data, mesh_handle});
          LOG("Loaded Mesh: %s Handle: %" PRIu64 "", mesh->mName.data, mesh_handle);
     }

     assimp_release_import(scene);
}

void Assimp_Mesh_Loader::shutdown( void )
{
	//Do Nothing
}

