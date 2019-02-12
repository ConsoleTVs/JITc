# Required project information.
cmake_minimum_required (VERSION 2.8)
project (JITc)

# Set the default build mode to release if not set.
if (NOT CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release)
endif ()

# Set the C general flags and flags for debug and release.
if (CMAKE_COMPILER_IS_GNUCXX)
    set (CMAKE_C_FLAGS "-Wall -Wextra")
    set (CMAKE_C_FLAGS_DEBUG "-g -D DEBUG=true")
    set (CMAKE_C_FLAGS_RELEASE "-Ofast -flto -D DEBUG=false")
endif (CMAKE_COMPILER_IS_GNUCXX)

# Set the C standard to use.
set (CMAKE_C_STANDARD 99)
set (CMAKE_C_STANDARD_REQUIRED ON)

# Set the output directories.
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Setup the final executable.
add_executable (JITc JITc.c src/lexer.c src/parser.c src/compiler.c)
