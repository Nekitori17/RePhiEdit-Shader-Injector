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

set(PROJECT_SOURCES src/main.cpp)

add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCES} ${MINHOOK_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE "${MINHOOK_DIR}/include")

target_link_options(${PROJECT_NAME}
PRIVATE
  -static
  -static-libgcc
  -static-libstdc++
)

if(MINGW)
  target_link_libraries(${PROJECT_NAME} psapi)
endif()

message(STATUS "Build setup OK! Project: ${PROJECT_NAME}")
