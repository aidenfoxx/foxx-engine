#########################################################
# Foxx Engine - Renderer
#########################################################

cmake_minimum_required(VERSION 3.3.2)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(foxx.renderer)

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
# Load OpenGL.
#
find_package(OPENGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

if(NOT OPENGL_FOUND)
	message(ERROR " Could not find OpenGL!")
endif(NOT OPENGL_FOUND)

#
#  Build library.
#
if (NOT TARGET foxx.renderer)
	add_library(foxx.renderer SHARED ${SRCS})
	add_dependencies(foxx.renderer foxx.core)
	target_link_libraries(foxx.renderer foxx.core ${OPENGL_LIBRARIES})
endif (NOT TARGET foxx.renderer)