cmake_minimum_required(VERSION 2.8.10)
cmake_policy(SET CMP0015 NEW)


### project definition

set(PROJECT prt4cmd)
project(prt4cmd)


### external dependencies

find_package(Boost COMPONENTS program_options filesystem)
include_directories(/opt/local/include)
link_directories(/opt/local/lib)
add_definitions(-DBOOST_MINOR_VERSION=48)


### prt dependencies

# if not specified on command line, assume default layout of CityEngine SDK 
if(NOT prt_DIR)
	set(prt_DIR "/Volumes/Volume2/jenkins_slave/workspace/prt4cmd/aad5cc30/com.esri.prt.clients.prt4cmd/src/../../cmake")
endif()
find_package(prt CONFIG)


### build target

add_executable(prt4cmd prt4cmd.cpp)

SET(CMAKE_INSTALL_RPATH "")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

include_directories(/Volumes/Volume2/jenkins_slave/workspace/prt4cmd/aad5cc30/prtsdk/include)
target_link_libraries(prt4cmd /Volumes/Volume2/jenkins_slave/workspace/prt4cmd/aad5cc30/prtsdk/bin/libcom.esri.prt.core.dylib /opt/local/lib/libboost_program_options-mt.dylib;/opt/local/lib/libboost_filesystem-mt.dylib)

if(Darwin STREQUAL "Linux")
	add_custom_command(
		TARGET prt4cmd POST_BUILD
		COMMAND /usr/bin/patchelf --set-rpath "\\\$$ORIGIN" prt4cmd
	)

elseif(Darwin STREQUAL "Darwin")
	add_custom_command(TARGET prt4cmd POST_BUILD COMMAND /usr/bin/install_name_tool
		-change @rpath/libcom.esri.prt.core.dylib 
		prt4cmd)

endif()

