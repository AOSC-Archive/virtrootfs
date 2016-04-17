cmake_minimum_required(VERSION 3.0)
project(virtrootfs)

option(STATIC_BUILD "Build a static version" ON)
if(${STATIC_BUILD})
set(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

file(GLOB_RECURSE VRFS_SRC RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" "src/*.c" "src/*.h")
add_executable(virtrootfs ${VRFS_SRC})
set_target_properties(virtrootfs PROPERTIES POSITION_INDEPENDENT_CODE ON)
add_definitions("-D_FILE_OFFSET_BITS=64")

# Link to bstrlib
add_library(bstrlib STATIC "lib/bstrlib/bsafe.c" "lib/bstrlib/bstraux.c" "lib/bstrlib/bstrlib.c" "lib/bstrlib/buniutil.c" "lib/bstrlib/utf8util.c")
target_include_directories(bstrlib INTERFACE "lib/bstrlib")
set_target_properties(bstrlib PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_link_libraries(virtrootfs PRIVATE bstrlib)

# Link to libfuse
include(FindPkgConfig)
pkg_search_module(FUSE REQUIRED fuse)
target_compile_options(virtrootfs PRIVATE ${FUSE_CFLAGS})
target_include_directories(virtrootfs PRIVATE ${FUSE_STATIC_INCLUDE_DIRS})
target_link_libraries(virtrootfs PRIVATE ${FUSE_STATIC_LIBRARIES})
