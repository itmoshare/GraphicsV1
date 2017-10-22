cmake_minimum_required(VERSION 3.8)
project(GraphicsV1)

set(CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_FLAGS "-pthread ${CMAKE_CXX_FLAGS}")
add_definitions(-D__STRICT_ANSI__)

set(SOURCE_FILES main.cpp CGame.cpp CGame.h UserInput.cpp UserInput.h Player.cpp Player.h Render.cpp Render.h GameState.cpp GameState.h Renders/ImageRender.cpp Renders/ImageRender.h Transform.cpp Transform.h)
add_executable(GraphicsV1 ${SOURCE_FILES})

include_directories(lib/glm)