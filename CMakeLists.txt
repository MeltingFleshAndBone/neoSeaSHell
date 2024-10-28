cmake_minimum_required(VERSION 3.10)

# Set the project name
project(SeaSHell VERSION 0.1.0 LANGUAGES C)

# Create a directory for binaries
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin/corelib)

# Specify the source files for the library
set(LIBRARY_SOURCES
    src/corelib/term.c
)

# Create a library from term.c
add_library(term_lib 
  STATIC ${LIBRARY_SOURCES}
)

# Specify the source file for the executable
set(EXECUTABLE_SOURCE
    src/main.c
)

# Create the executable and link it with the library
add_executable(SeaSHell ${EXECUTABLE_SOURCE})
target_link_libraries(SeaSHell PRIVATE term_lib)

# Set output directories for the library
set_target_properties(term_lib PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH})

