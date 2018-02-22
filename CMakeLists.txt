#########################################################
# Foxx Engine
#########################################################

cmake_minimum_required(VERSION 3.3.2)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(foxx.engine)

set(FOXX_VERSION_MAJOR 0)
set(FOXX_VERSION_MINOR 1)
set(FOXX_VERSION_PATCH 0)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall -O3")

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)

set(FOXX_RENDER_METHOD GL CACHE STRING "Render method.")
set_property(CACHE FOXX_RENDER_METHOD PROPERTY STRINGS GL D3D GLES)

set(FOXX_PACKAGE_LUA FALSE CACHE STRING "Include LUA bindings package.")
set_property(CACHE FOXX_PACKAGE_LUA PROPERTY STRINGS TRUE FALSE)

set(FOXX_PACKAGE_MANAGER FALSE CACHE STRING "Include manager package.")
set_property(CACHE FOXX_PACKAGE_MANAGER PROPERTY STRINGS TRUE FALSE)

set(FOXX_PACKAGE_PHYSICS TRUE CACHE STRING "Inlcude physics package.")
set_property(CACHE FOXX_PACKAGE_PHYSICS PROPERTY STRINGS TRUE FALSE)

set(FOXX_PACKAGE_RENDERER TRUE CACHE STRING "Include renderer package.")
set_property(CACHE FOXX_PACKAGE_RENDERER PROPERTY STRINGS TRUE FALSE)

#
# Add packages.
#
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/packages/foxx.core")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/packages/foxx.core/include")

if(FOXX_PACKAGE_LUA)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/packages/foxx.lua")
	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/packages/foxx.lua/include")
endif(FOXX_PACKAGE_LUA)

if(FOXX_PACKAGE_MANAGER)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/packages/foxx.manager")
	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/packages/foxx.manager/include")
endif(FOXX_PACKAGE_MANAGER)

if(FOXX_PACKAGE_PHYSICS)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/packages/foxx.physics")
	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/packages/foxx.physics/include")
endif(FOXX_PACKAGE_PHYSICS)

if(FOXX_PACKAGE_RENDERER)
	add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/packages/foxx.renderer")
	include_directories("${CMAKE_CURRENT_SOURCE_DIR}/packages/foxx.renderer/include")
endif(FOXX_PACKAGE_RENDERER)

#
# Set include directory.
#
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

#
# Load SRCs and remove application 
# entry points.
#
file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

set(SRCS_NOT_BINARIES)

foreach(SRC ${SRCS})
	if (NOT ${SRC} MATCHES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")
		list(APPEND SRCS_NOT_BINARIES ${SRC})
	endif (NOT ${SRC} MATCHES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c")
endforeach(SRC ${SRCS})

#
# Load PkgConfig.
#
find_package(PkgConfig REQUIRED)

if(NOT PkgConfig_FOUND)
	message(ERROR " Could not find PkgConfig!")
endif(NOT PkgConfig_FOUND)

#
#  Build engine.
#
add_executable(foxx.engine "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c" ${SRCS_NOT_BINARIES})
target_link_libraries(foxx.engine foxx.core)

#
#  Link packages.
#
add_dependencies(foxx.engine foxx.core)
target_link_libraries(foxx.engine foxx.core)

if(FOXX_PACKAGE_LUA)
	add_dependencies(foxx.engine foxx.lua)
	target_link_libraries(foxx.engine foxx.lua)
endif(FOXX_PACKAGE_LUA)

if(FOXX_PACKAGE_PHYSICS)
	add_dependencies(foxx.engine foxx.physics)
	target_link_libraries(foxx.engine foxx.physics)
endif(FOXX_PACKAGE_PHYSICS)

if(FOXX_PACKAGE_RENDERER)
	add_dependencies(foxx.engine foxx.renderer)
	target_link_libraries(foxx.engine foxx.renderer)
endif(FOXX_PACKAGE_RENDERER)