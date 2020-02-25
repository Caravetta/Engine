project( EngineCore )

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

set(INC_ECS
    "ecs/include/")

file(GLOB SRC_ECS
     "ecs/*.cpp"
     "ecs/*.c")

set(INC_DATA_STRUCT
    "data_structures/include/")

file(GLOB SRC_DATA_STRUCT
     "data_structures/*.cpp"
     "data_structures/*.c")

set(INC_UTILS
    "utils/include/")

file(GLOB SRC_UTILS
     "utils/*.cpp"
     "utils/*.c")

set(INC_MATH
    "math/include/")

file(GLOB SRC_MATH
     "math/*.cpp"
     "math/*.c")

set(INC_INPUT
    "input/include/")

file(GLOB SRC_INPUT
     "input/*.cpp"
     "input/*.c")

set(INC_GRAPHICS
    "graphics/include/")

file(GLOB SRC_GRAPHICS
     "graphics/*.cpp"
     "graphics/*.c")

set(INC_MEM
    "memory/include/")

file(GLOB SRC_MEM
     "memory/*.cpp"
     "memory/*.c")

set(INC_PLATFORM_GRAPHICS
    "platform/graphics/include/")

file(GLOB SRC_PLATFORM_GRAPHICS
     "platform/graphics/*.cpp"
     "platform/graphics/*.c")

set(INC_REFLECTION
    "reflection/include/")

file(GLOB SRC_REFLECTION
     "reflection/*.cpp"
     "reflection/*.c")

set(INC_GLOBAL
    "include/")

file(GLOB SRC_GLOBAL
     "*.cpp"
     "*.c")

set(INC_GLM
    "../libs/glm/glm"
    "../libs/glm/glm/detail"
    "../libs/glm/glm/ext"
    "../libs/glm/glm/gtc"
    "../libs/glm/glm/gtx"
    "../libs/glm/glm/simd")

if ( ${CMAKE_SYSTEM_NAME} MATCHES "Linux" )

     set(INC_PLATFORM
         "platform/include/"
         "platform/linux/include/")

     file(GLOB SRC_PLATFORM
          "platform/linux/*.cpp"
          "platform/linux/*.c")

elseif( ${CMAKE_SYSTEM_NAME} MATCHES "Windows" )

     set(INC_PLATFORM
         "platform/include/"
         "platform/win32/include/")

     file(GLOB SRC_PLATFORM
          "platform/win32/*.cpp"
          "platform/win32/*.c")

endif()

set(ALL_INC
    ${INC_ECS}
    ${INC_UTILS}
    ${INC_MATH}
    ${INC_INPUT}
    ${INC_GRAPHICS}
    ${INC_MEM}
    ${INC_PLATFORM_GRAPHICS}
    ${INC_REFLECTION}
    ${INC_GLOBAL}
    ${INC_PLATFORM}
    ${INC_GLM}
    ${INC_DATA_STRUCT})

set(ALL_SRC
    ${SRC_ECS}
    ${SRC_UTILS}
    ${SRC_MATH}
    ${SRC_INPUT}
    ${SRC_GRAPHICS}
    ${SRC_MEM}
    ${SRC_PLATFORM_GRAPHICS}
    ${SRC_REFLECTION}
    ${SRC_GLOBAL}
    ${SRC_PLATFORM}
    ${SRC_DATA_STRUCT})

foreach( inc ${ALL_INC})
     file(GLOB INC_GLOB "${inc}*.inl" "${inc}*.h")
     foreach( incfile ${INC_GLOB})
          set(FUNC_INPUT "${FUNC_INPUT}-i;${incfile};")
     endforeach()
endforeach()
set(FUNC_INPUT "${FUNC_INPUT}-o;core_component_gen.h;")

add_library(EngineCore MODULE ${ALL_SRC})
target_include_directories(EngineCore PUBLIC ${ALL_INC})

add_dependencies( EngineCore Introspector )

add_custom_target(base_comp_gen
                  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/../../build/src/introspection/Introspector.exe ${FUNC_INPUT}
                  COMMENT "Generating Component/Meta Data"
                  DEPENDS Introspector
                 )

add_dependencies(EngineCore base_comp_gen)

