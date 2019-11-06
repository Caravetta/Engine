add_subdirectory(platform/graphics/opengl)

#Set Comp Flags
set(CMAKE_CXX_FLAGS "${CXX_FLAGS_BASE}")

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
     set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-sign-compare -fPIC -Woverloaded-virtual -Wwrite-strings -Wno-unused")
     set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
     set(CMAKE_CXX_FLAGS_RELEASE "-O3")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX -DOPENGL -lX11 -lGL -lGLU -ldl")

elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWINDOWS -D_CRT_SECURE_NO_WARNINGS")

endif()

set(engine_core_src
    data_structures/bit_field.cpp
    data_structures/handle.cpp
    ecs/ecs.cpp
    ecs/entity.cpp
    ecs/entity_group.cpp
    ecs/component.cpp
    ecs/component_data.cpp
    ecs/component_data_array.cpp
    ecs/default_components.cpp
    ecs/system.cpp
    platform/graphics/platform_graphics.cpp
    utils/crc32.cpp
    utils/timer.cpp
    math/vector3f.cpp
    math/vector4f.cpp
    math/matrix4f.cpp
    input/key_input.cpp
    graphics/window.cpp
    graphics/mesh.cpp
    graphics/shader.cpp
    graphics/render_texture_info.cpp
    graphics/render_texture.cpp
    graphics/render_pass.cpp
    graphics/render_context.cpp
    graphics/material.cpp
    memory/page_allocator.cpp
    engine_core.cpp
    reflection/meta_base.cpp
    reflection/meta_struct.cpp
    reflection/meta_field.cpp
    reflection/meta_info.cpp
    reflection/reflection_system.cpp
    test.cpp)

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
set(engine_core_linux_src
    platform/linux/input_linux.cpp
    platform/linux/timer_linux.cpp
    platform/linux/window_linux.cpp)

add_executable(Engine-Core ${engine_core_src} ${engine_core_linux_src})
add_library(EngineCore STATIC ${engine_core_src} ${engine_core_linux_src})

elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
set(engine_core_win_src
    platform/win32/input_win32.cpp
    platform/win32/timer_win32.cpp
    platform/win32/window_win32.cpp)

add_executable(Engine-Core ${engine_core_src} ${engine_core_win_src})
add_library(EngineCore STATIC ${engine_core_src} ${engine_core_win_src})

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
                           platform/opengl/include
                           platform/opengl/include
                           platform/graphics/include
                           input/include
                           graphics/include
                           ../libs/glm/glm
                           ../libs/glm/glm/detail
                           ../libs/glm/glm/ext
                           ../libs/glm/glm/gtc
                           ../libs/glm/glm/gtx
                           ../libs/glm/glm/simd)

target_include_directories(EngineCore PUBLIC
                           include
                           data_structures/include
                           ecs/include
                           utils/include
                           reflection/include
                           math/include
                           memory/include
                           platform/include
                           platform/opengl/include
                           platform/opengl/include
                           platform/graphics/include
                           input/include
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

target_include_directories(EngineCore PUBLIC
                           platform/linux/include)

elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
target_include_directories(Engine-Core PUBLIC
                           platform/win32/include)

target_include_directories(EngineCore PUBLIC
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

