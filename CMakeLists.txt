cmake_minimum_required (VERSION 2.6)

project (Engine)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
     set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused")
     set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g3")
     set(CMAKE_CXX_FLAGS_RELEASE "-O3")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DLINUX -DOPENGL -lX11 -lGL -lGLU")
endif()

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCPU_X86")
endif()

add_subdirectory(src)

