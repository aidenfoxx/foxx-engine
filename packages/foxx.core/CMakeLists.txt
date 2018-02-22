#########################################################
# Foxx Engine - Core
#########################################################

cmake_minimum_required(VERSION 3.3.2)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(foxx.core)

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
# Load PkgConfig.
#
find_package(PkgConfig REQUIRED)

if(NOT PkgConfig_FOUND)
	message(ERROR " Could not find PkgConfig!")
endif(NOT PkgConfig_FOUND)

#
# Load SQLite3.
#
pkg_check_modules(SQLite3 REQUIRED sqlite3)

include_directories(${SQLite3_INCLUDE_DIRS})
link_directories(${SQLite3_LIBRARY_DIRS})
add_definitions(${SQLite3_CFLAGS_OTHER})

if(NOT SQLite3_FOUND)
	message(ERROR " Could not find SQLite3!")
endif(NOT SQLite3_FOUND)

#
#  Build library.
#
if (NOT TARGET foxx.core)
	add_library(foxx.core SHARED ${SRCS})
	target_link_libraries(foxx.core ${SQLite3_LIBRARIES})
endif (NOT TARGET foxx.core)