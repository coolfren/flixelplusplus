cmake_minimum_required(VERSION 3.14)

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_SOURCE_DIR}/mk")

message(STATUS "Source dir: ${CMAKE_SOURCE_DIR}")

project(flixel++, VERSION 0.1.0)
include_directories("include/")
include_directories("bundles/tinyxml2/")
file (GLOB_RECURSE FLIXEL_FILES CONFIGURE_DEPENDS "source/*.cpp" "bundles/tinyxml2/tinyxml2.cpp")

add_definitions(-DUSE_CURL)

if(DEFINED SDL_LEGACY)
    add_definitions(-DSDL_LEGACY)
    find_package(SDL_image REQUIRED)
    include_directories(${SDLIMAGE_INCLUDE_DIRS})

    find_package(SDL_ttf REQUIRED)
    include_directories(${SDLTTF_INCLUDE_DIRS})

    find_package(SDL REQUIRED)
    include_directories(${SDL_INCLUDE_DIRS})
else()
    find_package(SDL2_image REQUIRED)
    include_directories(${SDL2IMAGE_INCLUDE_DIRS})

    find_package(SDL2_ttf REQUIRED)
    include_directories(${SDL2TTF_INCLUDE_DIRS})

    find_package(SDL2 REQUIRED)
    include_directories(${SDL2_INCLUDE_DIRS})
endif()

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

find_package(OpenAL REQUIRED)
include_directories(${OPENAL_INCLUDE_DIR})

find_package(LibVorbisfile REQUIRED)
include_directories(${VORBIS_INCLUDE_DIR})

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

add_library(flixel++ SHARED ${FLIXEL_FILES})

if(DEFINED SDL_LEGACY)
    target_link_libraries(flixel++ ${SDL_LIBRARIES})
    target_link_libraries(flixel++ ${SDL_IMAGE_LIBRARIES})
    target_link_libraries(flixel++ ${SDL_TTF_LIBRARIES})
else()
    target_link_libraries(flixel++ ${SDL2_LIBRARIES})
    target_link_libraries(flixel++ ${SDL2_IMAGE_LIBRARIES})
    target_link_libraries(flixel++ ${SDL2_TTF_LIBRARIES})
endif()

target_link_libraries(flixel++ ${CURL_LIBRARIES})
target_link_libraries(flixel++ ${OPENAL_LIBRARY})
target_link_libraries(flixel++ ${VORBISFILE_LIBRARY})
target_link_libraries(flixel++ ${CURL_LIBRARY})

install(TARGETS flixel++ DESTINATION lib)
