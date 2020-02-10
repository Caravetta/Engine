
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

set(introspector_src
    token.cpp
    lexer.cpp
    introspection.cpp
    introspector.cpp)

add_executable(Introspector ${introspector_src})

target_include_directories(Introspector PUBLIC
                           include)

