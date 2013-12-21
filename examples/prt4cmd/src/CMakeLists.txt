cmake_minimum_required(VERSION 2.8.10)
cmake_policy(SET CMP0015 NEW)


### project definition

set(PROJECT prt4cmd)
project(prt4cmd)


### external dependencies

find_package(Boost COMPONENTS program_options filesystem)
include_directories(C:/local/boost_1_54_0)
link_directories(C:/local/boost_1_54_0/lib64-msvc-10.0)
add_definitions(-DBOOST_MINOR_VERSION=54)


### prt dependencies

# if not specified on command line, assume default layout of CityEngine SDK 
if(NOT prt_DIR)
	set(prt_DIR "C:/hudson/workspace/prt4cmd/f65d3bb2/com.esri.prt.clients.prt4cmd/src/../../cmake")
endif()
find_package(prt CONFIG)


### build target

add_executable(prt4cmd prt4cmd.cpp)

SET(CMAKE_INSTALL_RPATH "")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

include_directories(C:/hudson/workspace/prt4cmd/f65d3bb2/prtsdk/include)
target_link_libraries(prt4cmd C:/hudson/workspace/prt4cmd/f65d3bb2/prtsdk/bin/com.esri.prt.core.lib optimized;C:/local/boost_1_54_0/lib64-msvc-10.0/libboost_program_options-vc100-mt-1_54.lib;debug;C:/local/boost_1_54_0/lib64-msvc-10.0/libboost_program_options-vc100-mt-gd-1_54.lib;optimized;C:/local/boost_1_54_0/lib64-msvc-10.0/libboost_filesystem-vc100-mt-1_54.lib;debug;C:/local/boost_1_54_0/lib64-msvc-10.0/libboost_filesystem-vc100-mt-gd-1_54.lib)

if(Windows STREQUAL "Linux")
	add_custom_command(
		TARGET prt4cmd POST_BUILD
		COMMAND /usr/bin/patchelf --set-rpath "\\\$$ORIGIN" prt4cmd
	)

elseif(Windows STREQUAL "Darwin")
	add_custom_command(TARGET prt4cmd POST_BUILD COMMAND 
		-change @rpath/libcom.esri.prt.core.dylib 
		prt4cmd)

endif()

