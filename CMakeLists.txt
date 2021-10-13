cmake_minimum_required(VERSION 3.11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(Gusto-Engine)

find_package(OpenGL REQUIRED)

add_executable(game 
dependencies/glad.c
dependencies/imgui/imgui_demo.cpp
dependencies/imgui/imgui_draw.cpp
dependencies/imgui/imgui_impl_glfw.cpp
dependencies/imgui/imgui_impl_opengl3.cpp
dependencies/imgui/imgui_tables.cpp
dependencies/imgui/imgui_widgets.cpp
dependencies/imgui/imgui.cpp

src/System/FileManager.cpp
src/System/Shader.cpp
src/System/Texture.cpp
src/System/Color.cpp
src/System/Window.cpp
src/Graphics/RigidBody.cpp
src/Graphics/Shape.cpp
src/Physics/Collision.cpp
src/Physics/Space.cpp
src/main.cpp
)

target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(game PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

target_include_directories(game PUBLIC ${GLFW_INCLUDE_DIR})

if (UNIX)
target_link_libraries(game PUBLIC glfw ${CMAKE_DL_LIBS})
endif (UNIX)

if (WIN32)
target_link_options(game PUBLIC -static-libgcc -static-libstdc++)
target_link_libraries(game PUBLIC glfw3)
endif(WIN32)
