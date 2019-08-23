
set(engine_core_src
    data_structures/bit_field.cpp
    data_structures/handle.cpp
    ecs/ecs.cpp
    ecs/entity.cpp
    ecs/entity_group.cpp
    ecs/component.cpp
    ecs/component_data.cpp
    ecs/component_data_array.cpp
    reflection/meta_base.cpp
    reflection/meta_struct.cpp
    reflection/meta_field.cpp
    reflection/reflection_system.cpp
    utils/crc32.cpp
    math/vector3f.cpp
    graphics/window.cpp
    memory/page_allocator.cpp
    engine_core.cpp
    test.cpp)

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
set(engine_core_linux_src
    platform/linux/window_linux.cpp
    platform/linux/opengl_linux.cpp)

add_executable(Engine-Core ${engine_core_src} ${engine_core_linux_src})
endif()

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
add_executable(Engine-Core ${engine_core_src})
endif()

target_include_directories(Engine-Core PUBLIC
                           include
                           data_structures/include
                           ecs/include
                           utils/include
                           reflection/include
                           math/include
                           memory/include
                           platform/include
                           graphics/include)

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
target_include_directories(Engine-Core PUBLIC
                           platform/linux/include)

endif()

get_property(includes
             TARGET Engine-Core
             PROPERTY INTERFACE_INCLUDE_DIRECTORIES
            )

add_custom_target(base_comp_gen
                  COMMAND test
                  COMMENT "Generating Base Component Data"
                 )

add_dependencies(Engine-Core base_comp_gen)

