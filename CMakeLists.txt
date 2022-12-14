cmake_minimum_required(VERSION 3.1)

#todo: work on this

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/mk")
# print source dir
message(STATUS "Source dir: ${CMAKE_SOURCE_DIR}")

project(flixel++, VERSION 0.1.0)
include_directories("include/")
include_directories("src/")

#add cpp files to flixel++ library
file (GLOB_RECURSE FLIXEL_FILES CONFIGURE_DEPENDS "source/*.cpp")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenAL REQUIRED)
include_directories(${OPENAL_INCLUDE_DIR})

find_package(LibVorbis REQUIRED)
include_directories(${LibVorbis_INCLUDE_DIR})

add_library(flixel++ SHARED ${FLIXEL_FILES})

target_link_libraries(flixel++ ${SDL2_LIBRARIES})
target_link_libraries(flixel++ ${OPENAL_LIBRARY})
target_link_libraries(flixel++ ${LibVorbis_LIBRARIES})

install(TARGETS flixel++ DESTINATION lib)