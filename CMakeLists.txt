cmake_minimum_required(VERSION 3.10)
get_filename_component(PROJECT CMAKE_CURRENT_SOURCE_DIR NAME)
project(${PROJECT})

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)

# glad
add_subdirectory(deps)
include_directories(deps/glad/include)
include_directories(deps/tinyply/source)

link_libraries(glfw glad fmt::fmt-header-only glm tinyply)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# find shader source path
add_compile_definitions(ROOT_PATH="${CMAKE_CURRENT_SOURCE_DIR}/")

add_subdirectory(ch02)
add_subdirectory(ch03)
add_subdirectory(ch05)