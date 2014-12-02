##
 # Author: Renato Utsch Gonçalves
 # Computer Science, UFMG
 # Computer Graphics
 # Practical exercise 3 - Ray Tracer
 #
 # Copyright (c) 2014 Renato Utsch
 #
 # Permission is hereby granted, free of charge, to any person obtaining a copy
 # of this software and associated documentation files (the "Software"), to deal
 # in the Software without restriction, including without limitation the rights
 # to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 # copies of the Software, and to permit persons to whom the Software is
 # furnished to do so, subject to the following conditions:
 #
 # The above copyright notice and this permission notice shall be included in
 # all copies or substantial portions of the Software.
 #
 # THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 # IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 # FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 # AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 # LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 # OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 # THE SOFTWARE.
 ##

# CMakeLists.txt file for compiling the project with CMake.

# Basic configuration
cmake_minimum_required( VERSION 2.6 FATAL_ERROR )
project( raytracer C CXX )

set( RAYTRACER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR} )
set( RAYTRACER_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )

set( RAYTRACER_DEFINITIONS "" )

# Add gcc options
if( UNIX )
    set( RAYTRACER_DEFINITIONS
        "${RAYTRACER_DEFINITIONS} -Wall -Wextra -Werror -Wno-deprecated-declarations -Wno-unused-parameter -Wno-comment" )
endif()

# Boids sources
set( RAYTRACER_SOURCE_FILES "${RAYTRACER_SOURCE_DIR}/source/error.cpp"
                        "${RAYTRACER_SOURCE_DIR}/source/intersection.cpp"
                        "${RAYTRACER_SOURCE_DIR}/source/main.cpp"
                        "${RAYTRACER_SOURCE_DIR}/source/parser.cpp"
                        "${RAYTRACER_SOURCE_DIR}/source/Ppm.cpp"
                        "${RAYTRACER_SOURCE_DIR}/source/rayTracer.cpp"
                        "${RAYTRACER_SOURCE_DIR}/source/scene.cpp"
                        "${RAYTRACER_SOURCE_DIR}/source/types.cpp" )

# Compile
add_definitions( ${RAYTRACER_DEFINITIONS} )

add_executable( raytracer ${RAYTRACER_SOURCE_FILES} )
