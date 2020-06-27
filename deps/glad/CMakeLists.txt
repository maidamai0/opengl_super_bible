get_filename_component(module ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_library(${module} src/glad.c include/glad/glad.h)

target_include_directories(${module} PRIVATE include)
