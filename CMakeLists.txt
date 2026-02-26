cmake_minimum_required(VERSION 3.15)

project(libShaderInjector VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(MINHOOK_DIR "${CMAKE_SOURCE_DIR}/libs/minhook")
set(MINHOOK_SOURCES 
  "${MINHOOK_DIR}/src/buffer.c"
  "${MINHOOK_DIR}/src/hook.c"
  "${MINHOOK_DIR}/src/trampoline.c"
  "${MINHOOK_DIR}/src/hde/hde32.c"
  "${MINHOOK_DIR}/src/hde/hde64.c"
)

set(PROJECT_SOURCES 
  src/Offsets.h
  src/ModLoader.h
  src/ModLoader.cpp
  src/ShaderInjector.h
  src/ShaderInjector.cpp
  src/ZLibProxy.cpp
)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES} ${MINHOOK_SOURCES})

set_target_properties(${PROJECT_NAME} PROPERTIES
  OUTPUT_NAME "zlib1"
  PREFIX ""
)

target_include_directories(${PROJECT_NAME} PRIVATE "${MINHOOK_DIR}/include")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

if(MSVC)
  set_property(TARGET ${PROJECT_NAME} PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  message(STATUS "Configured for MSVC compiler")
endif()


message(STATUS "Build setup OK! Project: ${PROJECT_NAME}")