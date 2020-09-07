cmake_minimum_required(VERSION 3.10)
project(ciphers CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/externals/cage/cmake")
include(cage_all)
cage_default_init()
#cage_assets_add_data_path("${CMAKE_CURRENT_SOURCE_DIR}/data")

add_subdirectory(externals/cage)

file(GLOB_RECURSE ciphers-sources "sources/*")
add_executable(ciphers ${ciphers-sources})
target_link_libraries(ciphers cage-core)
cage_ide_category(ciphers ciphers)
cage_ide_sort_files(ciphers)
cage_ide_working_dir_in_place(ciphers)
