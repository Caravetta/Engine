#include "core_common.h"
#include "handle.h"
#include "ecs.h"
#include "windows.h"
#include "reflection_system.h"
#include "crc32.h"
#include "vector3f.h"
#include "component.h"

typedef uint32_t Component_ID;

void __test(std::vector<int> vec )
{
     for ( size_t ii = 0; ii < vec.size(); ii++ ) {
          LOG("%d", vec[ii]);
     }
}

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

struct Transform {
     COMPONENT_DECLARE( Transform );

     Engine::Vector3f position;
};

COMPONENT_DEFINE( Transform );

struct Transform_1 {
     COMPONENT_DECLARE( Transform_1 );

     Engine::Vector3f position;
};

COMPONENT_DEFINE( Transform_1 );

int main()
{
     Engine::Reflection::init_reflection_system();
     Engine::init_component_system();

     Engine::Vector3f vec(1, 4, 7);

     LOG("Sizeof Size_Test %d Sizeof Ref_Test %d", (int)sizeof(Size_Test), (int)sizeof(Ref_Test));

     Engine::Handle_Manager handle_manager;
     Engine::Handle handle = handle_manager.get_handle();
     Engine::Handle handle_1 = handle_manager.get_handle();
     LOG("Handle before free %" PRIu64 "", handle);
     LOG("Handle before free %" PRIu64 "", handle_1);
     uint32_t index = handle_index(handle);
     uint32_t phase = handle_phase(handle);
     LOG("Handle IDX %" PRIu32 "", index);
     LOG("Handle PHASE %" PRIu32 "", phase);
     handle_manager.free_handle(handle);
     handle = handle_manager.get_handle();
     handle_manager.free_handle(handle_1);
     handle_1 = handle_manager.get_handle();
     LOG("Handle after free %" PRIu64 "", handle);
     LOG("Handle after free %" PRIu64 "", handle_1);
     index = handle_index(handle);
     phase = handle_phase(handle);
     LOG("Handle IDX %" PRIu32 "", index);
     LOG("Handle PHASE %" PRIu32 "", phase);


     Engine::Archetype arche_test;
     arche_test.add_component(12, Engine::ARCHETYPE_COMPONENT);
     arche_test.add_component(1, Engine::ARCHETYPE_SHARED);
     arche_test.add_component(50, Engine::ARCHETYPE_COMPONENT);
     arche_test.add_component(60, Engine::ARCHETYPE_TAG);
     arche_test.add_component(33, Engine::ARCHETYPE_COMPONENT);

     Engine::Archetype arche_test_1;
     arche_test_1.add_component(12, Engine::ARCHETYPE_COMPONENT);
     arche_test_1.add_component(60, Engine::ARCHETYPE_TAG);
     arche_test_1.add_component(33, Engine::ARCHETYPE_COMPONENT);

     Engine::init_ecs();

     Engine::register_archetype("test", arche_test);
     Engine::register_archetype("test__1", arche_test_1);

     __test({1, 2, 3, 4, 5});

     Engine::Entity_Group main_group({12, 33});

     Engine::Component_Data_Array<int> data = main_group.get_component_data_array<int>();

     Engine::Meta_Struct* ref_struct = Engine::Reflection::get_meta_struct("Ref_Test");
     if ( ref_struct != NULL ) {
          ref_struct->print_struct_info();
     }

     LOG("Transform ID: %" PRIu32 "", Engine::component_id<Transform>());
     LOG("Transform_1 ID: %" PRIu32 "", Engine::component_id<Transform_1>());

     system("pause");

     return 0;
}
