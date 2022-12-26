cmake_minimum_required(VERSION 3.1)

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/mk")

message(STATUS "Source dir: ${CMAKE_SOURCE_DIR}")

project(flixel++, VERSION 0.1.0)
include_directories("include/")
include_directories("bundles/tinyxml2/")
file (GLOB_RECURSE FLIXEL_FILES CONFIGURE_DEPENDS "source/*.cpp" "bundles/tinyxml2/tinyxml2.cpp")

find_package(SDL2_image REQUIRED)
include_directories(${SDL2IMAGE_INCLUDE_DIRS})

find_package(SDL2_ttf REQUIRED)
include_directories(${SDL2TTF_INCLUDE_DIRS})

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenAL REQUIRED)
include_directories(${OPENAL_INCLUDE_DIR})

find_package(LibVorbisfile REQUIRED)
include_directories(${VORBIS_INCLUDE_DIR})

find_package(tinyxml2 REQUIRED)
include_directories(${TINYXML2_INCLUDE_DIR})

add_library(flixel++ SHARED ${FLIXEL_FILES})

target_link_libraries(flixel++ ${SDL2_LIBRARIES})
target_link_libraries(flixel++ ${SDL2_IMAGE_LIBRARIES})
target_link_libraries(flixel++ ${SDL2_TTF_LIBRARIES})
target_link_libraries(flixel++ ${OPENAL_LIBRARY})
target_link_libraries(flixel++ ${VORBISFILE_LIBRARY})
target_link_libraries(flixel++ ${tinyxml2_SHARED_LIBS})

install(TARGETS flixel++ DESTINATION lib)