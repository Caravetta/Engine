cmake_minimum_required (VERSION 2.6)

project (Engine)

if(CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
     set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCPU_X86")
endif()

set(CXX_FLAGS_BASE "${CMAKE_CXX_FLAGS}")

MACRO(SUBDIRLIST result curdir)
     FILE(GLOB children RELATIVE ${curdir} ${curdir}/*)
     SET(dirlist "")
     FOREACH(child ${children})
          IF(IS_DIRECTORY ${curdir}/${child})
               LIST(APPEND dirlist ${child})
          ENDIF()
     ENDFOREACH()
     SET(${result} ${dirlist})
ENDMACRO()

add_subdirectory(src)

