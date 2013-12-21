cmake_minimum_required(VERSION 2.8.10)
cmake_policy(SET CMP0015 NEW)


### project definition

set(PROJECT prt4cmd)
project(${PROJECT})


### external dependencies

find_package(Boost COMPONENTS program_options filesystem)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})
add_definitions(-DBOOST_MINOR_VERSION=${Boost_MINOR_VERSION})


### prt dependencies

# if not specified on command line, assume default layout of CityEngine SDK 
if(NOT prt_DIR)
	set(prt_DIR "${PROJECT_SOURCE_DIR}/../../cmake")
endif()
find_package(prt CONFIG)


### build target

add_executable(${PROJECT} prt4cmd.cpp)

SET(CMAKE_INSTALL_RPATH "")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)

include_directories(${PRT_INCLUDE_PATH})
target_link_libraries(${PROJECT} ${PRT_LIBRARY} ${Boost_LIBRARIES})

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath,'$ORIGIN'")

elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
	add_custom_command(TARGET ${PROJECT} POST_BUILD COMMAND ${CMAKE_INSTALL_NAME_TOOL}
		-change @rpath/libcom.esri.prt.core.dylib ${PRT_CORE_LIBRARY}
		${PROJECT})

endif()

