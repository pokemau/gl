cmake_minimum_required(VERSION 3.27)

project(GLGL)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2 -g -Wall -Wextra")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(
    lib/glad/include
    lib/glfw/include
    lib/stb
    lib/cglm/include
)

set(STB_SRC lib/stb/stb_image.c)
set(GLAD_SRC lib/glad/src/glad.c)

add_executable(${PROJECT_NAME}
    src/main.c
    src/util.c
    src/camera.c
    src/gfx/shader.c
    src/gfx/texture.c
    src/gfx/vao.c
    src/gfx/vbo.c
    src/gfx/window.c
    src/block/block.c
    src/world/chunk.c
    src/world/cubemap.c
    ${STB_SRC}
)

############## GLFW ###################
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

if (WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw opengl32 gdi32)
endif (WIN32)

if (UNIX)
    target_link_libraries(${PROJECT_NAME} PRIVATE glfw GL)
endif (UNIX)

############## GLAD ###################
add_library(glad STATIC ${GLAD_SRC})
target_include_directories(glad PRIVATE lib/glad/include)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
