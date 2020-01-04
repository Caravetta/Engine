
#Set Comp Flags
set(CMAKE_CXX_FLAGS "${CXX_FLAGS_BASE}")

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-sign-compare -fPIC -Woverloaded-virtual -Wwrite-strings -Wno-unused")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX -DOPENGL -lX11 -lGL -lGLU -ldl")

     #Set Release Flags
     set(CMAKE_CXX_FLAGS_RELEASE "-O3")

     #Set Debug Flags
     set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")

elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWINDOWS -D_CRT_SECURE_NO_WARNINGS")

endif()


set(opengl_lib_src
    ../../../utils/logger.cpp
    opengl_platform.cpp)

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )
set(opengl_lib_linux_src
    linux/opengl_linux.cpp)

add_library(OpenGL MODULE ${opengl_lib_src} ${opengl_lib_linux_src})

elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )
set(opengl_lib_win32_src
    win32/opengl_win32.cpp)

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
set(LIBS opengl32)
target_link_libraries(OpenGL ${LIBS})

target_include_directories(OpenGL PUBLIC
                           win32/include)
endif()

add_custom_command(TARGET OpenGL
                   POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:OpenGL> ../../../../../.)

