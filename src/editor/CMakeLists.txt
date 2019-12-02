#add_subdirectory(../core/platform/graphics/opengl)

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

set(editor_src
    ../core/data_structures/bit_field.cpp
    ../core/data_structures/handle.cpp
    ../core/ecs/ecs.cpp
    ../core/ecs/entity.cpp
    ../core/ecs/entity_group.cpp
    ../core/ecs/component.cpp
    ../core/ecs/component_data.cpp
    ../core/ecs/component_data_array.cpp
    ../core/ecs/default_components.cpp
    ../core/ecs/system.cpp
    ../core/platform/graphics/platform_graphics.cpp
    ../core/utils/crc32.cpp
    ../core/utils/timer.cpp
    ../core/math/vector3f.cpp
    ../core/math/vector4f.cpp
    ../core/math/matrix4f.cpp
    ../core/input/key_input.cpp
    ../core/graphics/window.cpp
    ../core/graphics/mesh.cpp
    ../core/graphics/shader.cpp
    ../core/graphics/render_texture_info.cpp
    ../core/graphics/render_texture.cpp
    ../core/graphics/render_pass.cpp
    ../core/graphics/render_context.cpp
    ../core/graphics/material.cpp
    ../core/graphics/camera.cpp
    ../core/graphics/basic_renderer.cpp
    ../core/memory/page_allocator.cpp
    ../core/engine_core.cpp
    gui/gui.cpp
    gui/imgui.cpp
    gui/imgui_draw.cpp
    gui/imgui_widgets.cpp
    gui/imgui_canvas.cpp
    panels/menu_bar_panel.cpp
    panels/console_panel.cpp
    panels/hierarchy_panel.cpp
    panels/inspector_panel.cpp
    panels/scene_panel.cpp
    panels/panels.cpp
    basic_shapes/cube.cpp
    editor_context.cpp
    entity_manager.cpp
    ../core/reflection/meta_base.cpp
    ../core/reflection/meta_struct.cpp
    ../core/reflection/meta_field.cpp
    ../core/reflection/meta_info.cpp
    ../core/reflection/reflection_system.cpp
    editor.cpp)

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
set(editor_linux_src
    ../core/platform/linux/input_linux.cpp
    ../core/platform/linux/timer_linux.cpp
    ../core/platform/linux/window_linux.cpp)

add_executable(Editor ${editor_src} ${editor_linux_src})

#add_library( assimp SHARED IMPORTED )
#set_target_properties( assimp PROPERTIES IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/src/editor/libassimp.so )

#TARGET_LINK_LIBRARIES(Editor assimp)


elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
set(editor_win_src
    ../core/platform/win32/input_win32.cpp
    ../core/platform/win32/timer_win32.cpp
    ../core/platform/win32/window_win32.cpp)

add_executable(Editor WIN32 ${editor_src} ${editor_win_src})

endif()

target_include_directories(Editor PUBLIC
                           include
                           gui/include
                           panels/include
                           basic_shapes/include
                           ../core/
                           ../core/include
                           ../core/data_structures/include
                           ../core/ecs/include
                           ../core/utils/include
                           ../core/reflection/include
                           ../core/math/include
                           ../core/memory/include
                           ../core/platform/include
                           ../core/platform/opengl/include
                           ../core/platform/opengl/include
                           ../core/platform/graphics/include
                           ../core/input/include
                           ../core/graphics/include
                           libs/assimp/include)

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
target_include_directories(Editor PUBLIC
                           ../core/platform/linux/include)

elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
target_include_directories(Editor PUBLIC
                           ../core/platform/win32/include)

target_link_libraries(Editor user32 gdi32 opengl32 winmm)
endif()

get_property(includes
             TARGET Editor
             PROPERTY INTERFACE_INCLUDE_DIRECTORIES
            )

