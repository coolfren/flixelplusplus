cmake_minimum_required(VERSION 3.25.1)

#todo: work on this

project(flixel++, VERSION 0.1.0)
include_directories("include/")
file(GLOB files
     "source/*.cpp"
)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenAL REQUIRED)
include_directories(${OPENAL_INCLUDE_DIR})

add_executable(flixel++ ${files})

target_link_libraries(flixel++ ${SDL2_LIBRARIES})
target_link_libraries(flixel++ ${OPENAL_LIBRARY})