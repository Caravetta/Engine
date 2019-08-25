#include "engine_core.h"

#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

struct Transform {
     COMPONENT_DECLARE( Transform );

     Engine::Vector3f position;
};

COMPONENT_DEFINE( Transform );

struct Mesh_Handle {
     COMPONENT_DECLARE( Mesh_Handle );

     uint64_t handle;
};

COMPONENT_DEFINE( Mesh_Handle );

int main(int argc, char** argv) {
     Engine::Rc_t rc = Engine::engine_init();
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("Failed to init engine rc=%d", rc);
          return -1;
     }

     Engine::Shader test_shader({{Engine::VERTEX_SHADER, ""},
                                 {Engine::VERTEX_SHADER, ""}});

     Engine::Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Test");

     Engine::Entity entity = Engine::create_entity();

     Engine::add_components(entity, {Engine::component_id<Transform>(),
                                     Engine::component_id<Mesh_Handle>()});

     Engine::Entity_Group group({Engine::component_id<Transform>(),
                                 Engine::component_id<Mesh_Handle>()});

     Engine::Component_Data_Array<Mesh_Handle> mesh_handles(group);

     for ( size_t ii = 0; ii < mesh_handles.size(); ii++ ) {
          LOG("MESH idx %zd = %" PRIu64 "", ii, mesh_handles[ii].handle);
          mesh_handles[ii].handle = ii + 1000;
     }

     for ( size_t ii = 0; ii < mesh_handles.size(); ii++ ) {
          LOG("MESH idx %zd = %" PRIu64 "", ii, mesh_handles[ii].handle);
     }

     while( window.is_closed() == false ) {
          window.update();
          glViewport(0, 0, window.width(), window.height());
          glClearColor(0.5f, 0.6f, 0.7f, 1.0f);
          glClear(GL_COLOR_BUFFER_BIT);
          window.swap_buffers();
     }
}

