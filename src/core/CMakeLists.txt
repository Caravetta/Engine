
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
    platform/opengl/shader_gl.cpp
    utils/crc32.cpp
    math/vector3f.cpp
    math/vector4f.cpp
    math/matrix4f.cpp
    graphics/window.cpp
    memory/page_allocator.cpp
    engine_core.cpp
    test.cpp)

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
set(engine_core_linux_src
    platform/linux/window_linux.cpp
    platform/linux/opengl_linux.cpp)

add_executable(Engine-Core ${engine_core_src} ${engine_core_linux_src})
elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
set(engine_core_win_src
    platform/win32/window_win32.cpp
    platform/win32/opengl_win32.cpp)

add_executable(Engine-Core ${engine_core_src} ${engine_core_win_src})

#add_library(Engine-Core SHARED ${engine_core_src} ${engine_core_win_src})
#set_target_properties(Engine-Core PROPERTIES
#                      PUBLIC_HEADER "engine_core.h;include/core_common.h"
#                      LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
endif()

message(STATUS "JOSH ${CMAKE_BINARY_DIR}")

target_include_directories(Engine-Core PUBLIC
                           include
                           data_structures/include
                           ecs/include
                           utils/include
                           reflection/include
                           math/include
                           memory/include
                           platform/include
                           platform/opengl/include
                           graphics/include
                           ../libs/glm/glm
                           ../libs/glm/glm/detail
                           ../libs/glm/glm/ext
                           ../libs/glm/glm/gtc
                           ../libs/glm/glm/gtx
                           ../libs/glm/glm/simd)

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
target_include_directories(Engine-Core PUBLIC
                           platform/linux/include)

elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
target_include_directories(Engine-Core PUBLIC
                           platform/win32/include)

target_link_libraries(Engine-Core user32 gdi32 opengl32 winmm)
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

#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/lib/include)

