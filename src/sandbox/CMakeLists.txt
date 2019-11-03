
#Set Comp Flags
set(CMAKE_CXX_FLAGS "${CXX_FLAGS_BASE}")

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-sign-compare -fPIC -Woverloaded-virtual -Wwrite-strings -Wno-unused")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX -lX11 -lGL -lGLU -ldl")

     #Set Release Flags
     set(CMAKE_CXX_FLAGS_RELEASE "-O3")

     #Set Debug Flags
     set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")

elseif(CMAKE_CXX_COMPILER_ID MATCHES MSVC)
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DWINDOWS -D_CRT_SECURE_NO_WARNINGS")

endif()

set(sandbox_lib_src
    sandbox.cpp)

add_library(Game MODULE ${sandbox_lib_src})

target_include_directories(OpenGL PUBLIC
                           ../core
                           ../core/include
                           ../core/reflection/include
                           ../core/ecs/include)

