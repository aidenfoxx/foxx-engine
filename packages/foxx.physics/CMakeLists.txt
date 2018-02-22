#########################################################
# Foxx Engine - Physics
#########################################################

cmake_minimum_required(VERSION 3.3.2)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(foxx.physics)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)

#
# Set include directory.
#
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

#
# Load SRCs and remove application 
# entry points.
#
file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

#
# Add packages.
#
if (NOT TARGET foxx.core)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../foxx.core" "${CMAKE_CURRENT_SOURCE_DIR}/build/foxx.core" EXCLUDE_FROM_ALL)
	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../foxx.core/include")
endif (NOT TARGET foxx.core)

#
# Load PkgConfig.
#
find_package(PkgConfig REQUIRED)

if(NOT PkgConfig_FOUND)
	message(ERROR " Could not find PkgConfig!")
endif(NOT PkgConfig_FOUND)

#
#  Build library.
#
if (NOT TARGET foxx.physics)
	add_library(foxx.physics SHARED ${SRCS})
	add_dependencies(foxx.physics foxx.core)
	target_link_libraries(foxx.physics foxx.core)
endif (NOT TARGET foxx.physics)