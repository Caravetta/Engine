#include "engine_core.h"
#include "windows.h"

struct Ref_Test : Engine::Reflection::Struct {
     META_STRUCT_DECLARE( Ref_Test );
     static void populate_meta_struct_func(Engine::Meta_Struct& comp);

     uint8_t a;
     uint8_t b;
     uint8_t i;
     uint64_t k;
};

struct Size_Test {
     uint8_t l;
     uint8_t a;
};

META_STRUCT_DEFINE( Ref_Test );

void Ref_Test::populate_meta_struct_func(Engine::Meta_Struct& comp)
{
     comp.add_field(&Ref_Test::a, "a");
     comp.add_field(&Ref_Test::b, "b");
     comp.add_field(&Ref_Test::k, "k");
     comp.add_field(&Ref_Test::i, "i");
}

struct Ref_Test_ : Engine::Reflection::Struct {
     META_STRUCT_DECLARE( Ref_Test_ );
     static void populate_meta_struct_func(Engine::Meta_Struct& comp);

     uint8_t a;
     uint8_t b;
};

META_STRUCT_DEFINE( Ref_Test_ );

void Ref_Test_::populate_meta_struct_func(Engine::Meta_Struct& comp)
{
     LOG("META_NAME: %s crc32: %" PRIu32 "", comp.__name, Engine::crc32(comp.__name));
}

struct Transform {
     COMPONENT_DECLARE( Transform );
     uint64_t test;
     //Engine::Vector3f position;
};

COMPONENT_DEFINE( Transform );

struct Transform_1 {
     COMPONENT_DECLARE( Transform_1 );
     float y;
     //Engine::Vector3f position;
};

COMPONENT_DEFINE( Transform_1 );

struct Mesh_Handle {
     COMPONENT_DECLARE( Mesh_Handle );

     uint64_t handle;
};

COMPONENT_DEFINE( Mesh_Handle );

int main()
{
     Engine::Rc_t rc = Engine::engine_init();
     if ( rc != Engine::SUCCESS ) {
          LOG_ERROR("Failed to init engine rc=%d", rc);
          return -1;
     }

     Engine::Meta_Struct* ref_struct = Engine::Reflection::get_meta_struct("Ref_Test");
     if ( ref_struct != NULL ) {
          ref_struct->print_struct_info();
     }

     LOG("Transform ID: %" PRIu32 "", Engine::component_id<Transform>());
     LOG("Transform_1 ID: %" PRIu32 "", Engine::component_id<Transform_1>());
     LOG("Mesh_Handle ID: %" PRIu32 "", Engine::component_id<Mesh_Handle>());

#if 1
     Engine::Entity entity = Engine::create_entity();
#endif
     Engine::Entity entity_1 = Engine::create_entity({Engine::component_id<Transform>(),
                                                      Engine::component_id<Transform_1>()});

     Transform* transform = Engine::get_component<Transform>(entity_1);
     if ( transform == NULL ) {
          return -1;
     }

     transform->test = 123;

     LOG("Transform Test before add %" PRIu64 "", transform->test);
#if 1
     Engine::Entity entity_2 = Engine::create_entity({Engine::component_id<Transform>()});

     Engine::Entity entity_3 = Engine::create_entity({Engine::component_id<Transform>(),
                                                      Engine::component_id<Transform_1>()});

     Engine::add_components(entity, {Engine::component_id<Transform>(),
                                     Engine::component_id<Mesh_Handle>()});
#endif
     Engine::add_component(entity_1, Engine::component_id<Mesh_Handle>());

     Mesh_Handle* mesh = Engine::get_component<Mesh_Handle>(entity_1);
     if ( mesh == NULL ) {
          return -1;
     }

     mesh->handle = 245;

     Mesh_Handle* mesh_1 = Engine::get_component<Mesh_Handle>(entity_1);
     if ( mesh == NULL ) {
          return -1;
     }

     transform = Engine::get_component<Transform>(entity_1);
     if ( transform == NULL ) {
          return -1;
     }

     LOG("Transform Test After add %" PRIu64 "", transform->test);

     LOG("Mesh_1 Handle value= %" PRIu64 "", mesh_1->handle);
#if 1
     LOG("\n////BEFORE DELETES/////////////\n");
     Engine::ecs_debug_print();

     Engine::delete_entity(entity_2);
     Engine::delete_entity(entity);
     Engine::delete_entity(entity_3);
     Engine::delete_entity(entity_1);

     LOG("\n////AFTER DELETES/////////////\n");
     Engine::ecs_debug_print();

     LOG("\n////AFTER CREATE/////////////\n");
     entity = Engine::create_entity();
     entity_1 = Engine::create_entity({Engine::component_id<Transform>(),
                                       Engine::component_id<Transform_1>()});

     entity_2 = Engine::create_entity({Engine::component_id<Transform>()});

     entity_3 = Engine::create_entity({Engine::component_id<Transform>(),
                                       Engine::component_id<Transform_1>()});

     Engine::add_components(entity, {Engine::component_id<Transform>(),
                                     Engine::component_id<Mesh_Handle>()});

     Engine::remove_component(entity_3, Engine::component_id<Transform>());

#endif

     for ( size_t ii = 0; ii < 10000; ii++ ) {
          entity_3 = Engine::create_entity({Engine::component_id<Transform>(),
                                            Engine::component_id<Transform_1>()});
     }

     Engine::ecs_debug_print();

     Engine::Entity_Group group({Engine::component_id<Mesh_Handle>(),
                                 Engine::component_id<Transform>()});

     Engine::Component_Data_Array a(group);
     system("pause");
     return 0;
}
