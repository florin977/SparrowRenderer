cmake_minimum_required(VERSION 3.10)

project(SparrowRenderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/main.cpp
    src/glad.c
    src/stb_image.cpp
    src/Shader.cpp
    src/Window.cpp
    src/Buffers/VertexBuffer.cpp
    src/Buffers/VertexArray.cpp
    src/Buffers/ElementBuffer.cpp
    src/Texture.cpp
)

add_executable(prg ${SOURCES})

target_include_directories(prg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(prg PRIVATE OpenGL::GL glfw)