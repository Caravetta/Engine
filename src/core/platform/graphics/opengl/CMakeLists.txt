
set(opengl_lib_src
    opengl_platform.cpp)

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
set(opengl_lib_linux_src
    linux/opengl_linux.cpp)

add_library(OpenGL MODULE ${opengl_lib_src} ${opengl_lib_linux_src})

elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
set(opengl_lib_win32_src
    linux/opengl_win32.cpp)

add_library(OpenGL MODULE ${opengl_lib_src} ${opengl_lib_win32_src})

endif()

target_include_directories(OpenGL PUBLIC
                           ../../../include
                           ../include
                           ../../../math/include
                           ../../../reflection/include/
                           ../../../utils/include/
                           ../../../graphics/include/
                           include)

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
target_include_directories(OpenGL PUBLIC
                           linux/include)

elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
target_include_directories(OpenGL PUBLIC
                           win32/include)

endif()

