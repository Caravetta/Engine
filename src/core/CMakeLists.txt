
set(engine_core_src
    data_structures/bit_field.cpp
    data_structures/handle.cpp
    ecs/ecs.cpp
    ecs/entity_system.cpp
    ecs/archetype_system.cpp
    ecs/archetype.cpp
    ecs/component.cpp
    ecs/entity_group.cpp
    reflection/meta_base.cpp
    reflection/meta_struct.cpp
    reflection/meta_field.cpp
    reflection/reflection_system.cpp
    utils/crc32.cpp
    math/vector3f.cpp
    test.cpp)

add_executable(Engine-Core ${engine_core_src})

target_include_directories(Engine-Core PUBLIC
                           include
                           data_structures/include
                           ecs/include
                           utils/include
                           reflection/include
                           math/include)

get_property(includes
             TARGET Engine-Core
             PROPERTY INTERFACE_INCLUDE_DIRECTORIES
            )

message(STATUS "Included directories for target ${target_name}")
foreach(dir ${includes})
     message(STATUS "dir='${dir}'")
endforeach()

add_custom_target(base_comp_gen
                  COMMAND test
                  COMMENT "Generating Base Component Data"
                 )

add_dependencies(Engine-Core base_comp_gen)

