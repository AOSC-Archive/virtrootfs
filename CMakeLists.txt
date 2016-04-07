project(virtrootfs)
cmake_minimum_required(VERSION 3.5)
include_directories(
	include
)
aux_source_directory(
	src DIR_SRCS
)
set(VIRTROOTFS_SRCS ${DIR_SRCS})

add_definitions(-D_FILE_OFFSET_BITS=64)

add_executable(virtrootfs ${DIR_SRCS})

if(NOT FORCE_SHARED)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
set_target_properties(virtrootfs PROPERTIES LINK_SEARCH_END_STATIC 1)
set(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
else(NOT FORCE_SHARED)
message( "You are trying to build a dynamically-linked virtrootfs, this is only for debug purpose" )
message( "and should *NOT* be used in production environment!" )
endif(NOT FORCE_SHARED)
target_link_libraries(virtrootfs fuse)
