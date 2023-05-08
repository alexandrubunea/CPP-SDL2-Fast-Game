cmake_minimum_required(VERSION 3.0.0)
project(Fast VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(SDL2 REQUIRED)

# It was a hell to configure this, but it works now
# For a reason I don't know, I had to use the x86_64-w64-mingw32 folder
# Because CMake, or SDL2_image CMake Config, or something else, was looking for the wrong folder (or something like that)
# I don't know why, but it works now, so I'm not complaining
# But I think it only works on Windows, probably works on Linux too with a few changes.
# I'm not sure if it works on MacOS, but I don't care, I don't have a Mac.
# I was searching for a solution for 3 hours, and I couldn't make it works with CMake GUI.
# I hate CMake, but I love it at the same time.
# I'm not sure if I'm doing something wrong, but I don't care, it works now.
set(SDL2_IMAGE_INCLUDE_DIRS "C:/SDL2/SDL2_image/x86_64-w64-mingw32/include/SDL2")
set(SDL2_IMAGE_LIBRARIES "C:/SDL2/SDL2_image/x86_64-w64-mingw32/lib/libSDL2_image.dll.a")

set(SDL2_TTF_INCLUDE_DIRS "C:/SDL2/SDL2_ttf/x86_64-w64-mingw32/include/SDL2")
set(SDL2_TTF_LIBRARIES "C:/SDL2/SDL2_ttf/x86_64-w64-mingw32/lib/libSDL2_ttf.dll.a")

include_directories(${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS} source)

add_executable(Fast 
    source/main.cpp
    source/resources/Application.cpp
    source/resources/Core.cpp
    source/resources/GameObject.cpp
    source/resources/Player.cpp
    source/resources/Car.cpp
    source/resources/Pickup.cpp
    source/resources/GUI/Text.cpp
)

target_link_libraries(Fast ${SDL2_IMAGE_LIBRARIES} ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})

message(STATUS "SDL2_INCLUDE_DIRS: " ${SDL2_INCLUDE_DIRS})
message(STATUS "SDL2_LIBRARIES: " ${SDL2_LIBRARIES})
message(STATUS "SDL2_IMAGE_INCLUDE_DIRS: " ${SDL2_IMAGE_INCLUDE_DIRS})
message(STATUS "SDL2_IMAGE_LIBRARIES: " ${SDL2_IMAGE_LIBRARIES})
message(STATUS "SDL2_TTF_INCLUDE_DIRS: " ${SDL2_TTF_INCLUDE_DIRS})
message(STATUS "SDL2_TTF_LIBRARIES: " ${SDL2_TTF_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)