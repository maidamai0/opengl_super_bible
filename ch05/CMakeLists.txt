get_filename_component(module ${CMAKE_CURRENT_SOURCE_DIR} NAME)
source_group(${module})

file(GLOB srcs *.cpp)

foreach(src ${srcs})
    get_filename_component(target ${src} NAME)
    add_executable(${target} ${src})
endforeach()