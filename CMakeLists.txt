cmake_minimum_required(VERSION 3.29)
project(HalfBakedEngine)

set(CMAKE_CXX_STANDARD 14)

# Find and include GLFW3
find_package(glfw3 3.3 REQUIRED)
include_directories(${GLFW3_INCLUDE_DIRS})
message(STATUS "GLFW3_INCLUDE_DIRS: ${GLFW3_INCLUDE_DIRS}")

# Find and include OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Include GLEW headers
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
message(STATUS "GLEW_INCLUDE_DIRS: ${GLEW_INCLUDE_DIRS}")

# Create executable
add_executable(HalfBakedEngine
        src/main.cpp
        src/render.cpp
)

# Link libraries
target_link_libraries(HalfBakedEngine
        glfw
        ${OPENGL_LIBRARIES}
        ${GLEW_LIBRARIES}
        stdc++fs
)
message(STATUS "GLFW3_LIBRARIES: ${GLFW3_LIBRARIES}")
message(STATUS "GLEW_LIBRARIES: ${GLEW_LIBRARIES}")
