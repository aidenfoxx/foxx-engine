#########################################################
# Foxx Engine
#########################################################

cmake_minimum_required(VERSION 3.3.2)

project(foxx-engine)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

set(MODEL_EDITOR TRUE CACHE STRING "Compile the model editor.")
set_property(CACHE MODEL_EDITOR PROPERTY STRINGS TRUE FALSE)

set(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/bin" CACHE PATH "Path to output executables.")

#
# Set Includes directories.
#
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

#
# Load SRCs and remove application 
# entry points.
#
file(GLOB_RECURSE SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")

set(SRCS_NOT_MAIN)

foreach(SRC ${SRCS})
	if (NOT ${SRC} MATCHES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c" AND NOT ${SRC} MATCHES "${CMAKE_CURRENT_SOURCE_DIR}/src/model-editor.c")
		list(APPEND SRCS_NOT_MAIN ${SRC})
	endif (NOT ${SRC} MATCHES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c" AND NOT ${SRC} MATCHES "${CMAKE_CURRENT_SOURCE_DIR}/src/model-editor.c")
endforeach(SRC ${SRCS})

#
# Define application executables.
#
add_executable(foxx "${CMAKE_CURRENT_SOURCE_DIR}/src/main.c" ${SRCS_NOT_MAIN})

if (MODEL_EDITOR MATCHES TRUE)
	add_executable(model-editor "${CMAKE_CURRENT_SOURCE_DIR}/src/model-editor.c" ${SRCS_NOT_MAIN})
endif (MODEL_EDITOR MATCHES TRUE)

#
# Load LibArchive.
#
find_package(LibArchive)

include_directories(${LibArchive_INCLUDE_DIRS})

if(NOT LibArchive_FOUND)
	message(ERROR " COULD NOT FIND LibArchive!")
endif(NOT LibArchive_FOUND)

#
# Load OpenGL.
#
find_package(OPENGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS})

if(NOT OPENGL_FOUND)
	message(ERROR " COULD NOT FIND OPENGL!")
endif(NOT OPENGL_FOUND)

#
# Load FreeGLUT.
#
find_package(GLUT REQUIRED)

include_directories(${GLUT_INCLUDE_DIRS})

if(NOT GLUT_FOUND)
	message(ERROR " COULD NOT FIND FREEGLUT!")
endif(NOT GLUT_FOUND)

#
# Load PkgConfig.
#
find_package(PkgConfig REQUIRED)

if(NOT PkgConfig_FOUND)
	message(ERROR " COULD NOT FIND PKGCONFIG!")
endif(NOT PkgConfig_FOUND)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})

if(NOT GTK3_FOUND)
	message(ERROR " COULD NOT FIND GTK3!")
endif(NOT GTK3_FOUND)

#
# Link Libraries (LibArchive, OpenGL, FreeGLUT, GTK+3).
#
target_link_libraries(foxx ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${LibArchive_LIBRARIES})

if (MODEL_EDITOR MATCHES TRUE)
	target_link_libraries(model-editor ${OPENGL_LIBRARIES} ${LibArchive_LIBRARIES} ${GTK3_LIBRARIES})
endif (MODEL_EDITOR MATCHES TRUE)