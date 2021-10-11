cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Gusto-Engine)


file(GLOB_RECURSE SRC_FILES src/*.cpp src/*.c)

find_package(OpenGL REQUIRED)

add_executable(game ${SRC_FILES})

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/Dependencies)

target_include_directories(game PUBLIC ${GLFW_INCLUDE_DIR})

if (UNIX)
target_link_libraries(game PUBLIC glfw ${CMAKE_DL_LIBS})
endif (UNIX)

if (WIN32)
target_link_options(game PUBLIC -static-libgcc -static-libstdc++)
target_link_libraries(game PUBLIC glfw3)
endif(WIN32)