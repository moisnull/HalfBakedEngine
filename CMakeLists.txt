cmake_minimum_required(VERSION 3.29)
project(HalfBakedEngine)

set(CMAKE_CXX_STANDARD 14)

# Find and include GLFW3
find_package(glfw3 3.3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIRS})
message(STATUS "GLFW3_INCLUDE_DIRS: ${GLFW3_INCLUDE_DIRS}")

# Find and include GLAD
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
add_library(glad STATIC src/glad.c)

add_executable(HalfBakedEngine
        src/main.cpp
)

target_link_libraries(HalfBakedEngine
        glfw
        ${OPENGL_LIBRARIES}
        glad
)
message(STATUS "GLFW3_LIBRARIES: ${GLFW3_LIBRARIES}")