# Set the minimum version of CMake
cmake_minimum_required(VERSION 3.15)

# Add the tests directory
project(tests)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Collect all test files in the folder
file(GLOB TEST_SOURCES "*.c")

# Add executables for each test file
foreach(TEST_SOURCE ${TEST_SOURCES})
    # Extract the filename without an extension to name the test
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    
    # Create a test executable
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    
    # Link the zedc_ascii static library and the absolute path of libzz.a
    target_link_libraries(${TEST_NAME} zedc_ascii ${LIBZZ_FOUND_PATH}/libzz.a)
endforeach()


set(TEST_SCRIPT "${CMAKE_SOURCE_DIR}/tests/tests.sh")

add_custom_target(run-tests
    COMMAND ${CMAKE_COMMAND} -E echo "Running tests with ${TEST_SCRIPT}"
    COMMAND ${TEST_SCRIPT}  
    DEPENDS ${TEST_SOURCES} 
    COMMENT "Running all tests with script"
)
