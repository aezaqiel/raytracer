cmake_minimum_required(VERSION 3.12)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "" FORCE)

project(raytracer C)

find_package(OpenGL REQUIRED)
add_subdirectory(vendor/glfw)
add_subdirectory(vendor/cglm)

add_executable(${PROJECT_NAME}
    src/main.c
    src/utilities.h
    src/ray.h
    src/ray.c
    src/hittable.h
    src/sphere.h
    src/sphere.c
    src/hittable_list.h
    src/hittable_list.c
    src/camera.h
    src/camera.c
)

target_include_directories(${PROJECT_NAME}
PRIVATE
    src
    OpenGL::Headers
    vendor/glfw/include
    vendor/cglm/include
    vendor/stb
)

target_link_libraries(${PROJECT_NAME}
PRIVATE
    OpenGL::GL
    glfw
    cglm
)
