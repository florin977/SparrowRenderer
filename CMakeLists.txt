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
    src/Material.cpp
    src/Mesh.cpp
    src/Model.cpp
    src/Entity.cpp
    src/Camera.cpp
)

include(FetchContent)

# Turns off Assimp's tests, tools, and extra bloat
set(ASSIMP_BUILD_TESTS OFF CACHE BOOL "Disable tests" FORCE)
set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "Disable tools" FORCE)
set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "Build zlib internally" FORCE) 
set(ASSIMP_INSTALL OFF CACHE BOOL "Disable installation step" FORCE)
set(ASSIMP_WARNINGS_AS_ERRORS OFF CACHE BOOL "Disable warnings as errors in Assimp" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build Assimp as a static library" FORCE)

FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v6.0.5
)

FetchContent_MakeAvailable(assimp)

add_executable(prg ${SOURCES})

target_include_directories(prg PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(OpenGL_GL_PREFERENCE GLVND)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

target_link_libraries(prg PRIVATE OpenGL::GL glfw assimp)