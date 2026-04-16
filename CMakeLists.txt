cmake_minimum_required(VERSION 3.10)
project(zedc_ascii C ASM) 

# Set include and source directories
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)


# Add include directory for headers
include_directories(${INCLUDE_DIR})

# Initialize a variable to store library paths
set(LIBZZ_PATHS)

# Add the fixed directory
list(APPEND LIBZZ_PATHS /usr/lpp/hzc/lib/)

# Retrieve the environment variable ZOPEN_OLD_LIBPATH and split it by ':'
if(DEFINED ENV{ZOPEN_OLD_LIBPATH})
    string(REPLACE ":" ";" ZOPEN_OLD_LIBPATH_LIST $ENV{ZOPEN_OLD_LIBPATH})
    list(APPEND LIBZZ_PATHS ${ZOPEN_OLD_LIBPATH_LIST})
endif()

# Find the library 'libzz.a' in the specified paths
set(LIBZZ_FOUND_PATH "")
foreach(PATH ${LIBZZ_PATHS})
    if(EXISTS "${PATH}/libzz.a")
        set(LIBZZ_FOUND_PATH ${PATH})
        break()
    endif()
endforeach()

# Handle the case where the library is not found
if(LIBZZ_FOUND_PATH)
    message(STATUS "Found libzz.a in: ${LIBZZ_FOUND_PATH}")
else()
    message(FATAL_ERROR "libzz.a not found in any of the specified paths")
endif()

# Generate the pkg-config file
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/zlib.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/zlib.pc"
    @ONLY
)

# Install the pkg-config file
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/zlib.pc"
    DESTINATION "lib/pkgconfig"
)

add_subdirectory(src)
add_subdirectory(tests)


if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  SET(CMAKE_INSTALL_PREFIX "." CACHE PATH "install path" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

add_custom_target(check
    COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target run-tests
    COMMENT "Running all tests defined in the tests folder"
)
