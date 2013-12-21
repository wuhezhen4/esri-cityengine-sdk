cmake_minimum_required(VERSION 2.8.10)
cmake_policy(SET CMP0015 NEW)


### project definition

set(PROJECT prt4cmd)
project(prt4cmd)


### external dependencies

find_package(Boost COMPONENTS program_options filesystem)
include_directories(/usr/include)
link_directories(/usr/lib64)
add_definitions(-DBOOST_MINOR_VERSION=34)


### prt dependencies

# if not specified on command line, assume default layout of CityEngine SDK 
if(NOT prt_DIR)
	set(prt_DIR "/tmp/hudson/workspace/prt4cmd/615bc431/com.esri.prt.clients.prt4cmd/src/../../cmake")
endif()
find_package(prt CONFIG)


### build target

add_executable(prt4cmd prt4cmd.cpp)

SET(CMAKE_INSTALL_RPATH "")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

include_directories(/tmp/hudson/workspace/prt4cmd/615bc431/prtsdk/include)
target_link_libraries(prt4cmd /tmp/hudson/workspace/prt4cmd/615bc431/prtsdk/bin/libcom.esri.prt.core.so /usr/lib64/libboost_program_options-mt.so;/usr/lib64/libboost_filesystem-mt.so)

if(Linux STREQUAL "Linux")
	set(CMAKE_EXE_LINKER_FLAGS "  -Wl,-rpath,'$ORIGIN' -Wl,-rpath,'$ORIGIN'")

elseif(Linux STREQUAL "Darwin")
	add_custom_command(TARGET prt4cmd POST_BUILD COMMAND 
		-change @rpath/libcom.esri.prt.core.dylib 
		prt4cmd)

endif()

