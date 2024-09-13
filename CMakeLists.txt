cmake_minimum_required(VERSION 3.5)
project(Raycaster)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Find SDL2
if (WIN32)
    # On Windows, specify the path to SDL2 manually
    set(SDL2_PATH "path/to/your/SDL2")
    set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include")
    set(SDL2_LIB_DIR "${SDL2_PATH}/lib")
    include_directories(${SDL2_INCLUDE_DIR})
    link_directories(${SDL2_LIB_DIR})
    set(SDL2_LIBRARIES SDL2 SDL2main)
else()
    # On Linux, use pkg-config to find SDL2
    find_package(PkgConfig REQUIRED)
    pkg_search_module(SDL2 REQUIRED sdl2)
    include_directories(${SDL2_INCLUDE_DIRS})
    link_directories(${SDL2_LIBRARY_DIRS})
endif()

# Source files
file(GLOB SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)

# Create the executable
add_executable(${PROJECT_NAME} ${SRC})

# Link SDL2 libraries
if (WIN32)
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
else()
    target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})
endif()