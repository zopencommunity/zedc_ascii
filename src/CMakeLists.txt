set(libsrc
  zedc_ascii.c
)

add_library(libzedc_ascii OBJECT ${libsrc})
add_library(zedc_ascii STATIC $<TARGET_OBJECTS:libzedc_ascii>)

# Create symlink libz.a -> libzedc_ascii.a in the build directory
add_custom_command(TARGET zedc_ascii POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E create_symlink libzedc_ascii.a libz.a
    WORKING_DIRECTORY ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}
)

install(
    DIRECTORY ${PROJECT_BINARY_DIR}/lib/
    DESTINATION "lib"
    FILES_MATCHING PATTERN "*.?")

# Install the symlink libz.a
install(CODE "
  set(LIB_DIR \"\$ENV{DESTDIR}\${CMAKE_INSTALL_PREFIX}/lib\")
  execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory \"\${LIB_DIR}\")
  execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink libzedc_ascii.a \"\${LIB_DIR}/libz.a\")
")

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION "include"
    FILES_MATCHING PATTERN "*")
