set(libsrc
  zedc_ascii.c
)

add_library(libzedc_ascii OBJECT ${libsrc})
add_library(zedc_ascii STATIC $<TARGET_OBJECTS:libzedc_ascii>)

install(
    DIRECTORY ${PROJECT_BINARY_DIR}/lib/
    DESTINATION "lib"
    FILES_MATCHING PATTERN "*.?")

install(
    DIRECTORY ${CMAKE_SOURCE_DIR}/include/
    DESTINATION "include"
    FILES_MATCHING PATTERN "*")
