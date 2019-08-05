#include "core_common.h"
#include "handle.h"
#include "ecs.h"
#include "windows.h"
#include "reflection_system.h"
#include "crc32.h"

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
};

META_STRUCT_DEFINE( Ref_Test );

void Ref_Test::populate_meta_struct_func(Engine::Meta_Struct& comp)
{
     LOG("META_NAME: %s crc32: %" PRIu32 "", comp.__name, Engine::crc32(comp.__name));
}

int main()
{
     Engine::Reflection::init_reflection_system();
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

     system("pause");

     return 0;
}
