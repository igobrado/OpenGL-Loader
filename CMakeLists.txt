# Configure CMake project
cmake_minimum_required(VERSION 3.1)
project("OpenGL-PBR")

# Add local CMake module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(OPENGL_PBR_SOURCES)
set(OPENGL_PBR_HEADERS)

# Assure OpenGL package was found or manually entered successfully
if(EXISTS "${OPENGL_INCLUDE_DIRS}" AND EXISTS "${OPENGL_LIBRARIES}")
    set(OPENGL_FOUND ON)
else()
    # Try to find OpenGL package
    find_package("OpenGL")
    if(NOT OPENGL_FOUND)
        message(FATAL_ERROR "OpenGL was not found.")
    endif()
endif()

# Assure GLEW package was found or manually entered successfully
if(EXISTS "${GLEW_INCLUDE_DIRS}" AND EXISTS "${GLEW_LIBRARIES}")
    set(GLEW_FOUND ON)
else()
    # Try to find GLEW package
    find_package("GLEW")
    if(NOT GLEW_FOUND)
        message(FATAL_ERROR "GLEW was not found.")
    endif()
endif()

# Assure GLFW package was found or manually entered successfully
if(EXISTS "${GLFW_INCLUDE_DIRS}" AND EXISTS "${GLFW_LIBRARIES}")
    set(GLFW_FOUND ON)
else()
    # Try to find GLFW package
    find_package("GLFW")
    if(NOT GLFW_FOUND)
        message(FATAL_ERROR "GLFW was not found.")
    endif()
endif()

# Assure GLM package was found or manually entered successfully
if(EXISTS "${GLM_INCLUDE_DIRS}")
    set(GLM_FOUND ON)
else()
    # Try to find GLM package
    find_package("GLM")
    if(NOT GLM_FOUND)
        message(FATAL_ERROR "GLM was not found.")
    endif()
endif()

include("${CMAKE_CURRENT_LIST_DIR}/src/CMakeLists.txt")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

target_include_directories(
        OpenGL-PBR PUBLIC

        "${OPENGL_INCLUDE_DIRS}"
        "${GLEW_INCLUDE_DIRS}"
        "${GLFW_INCLUDE_DIRS}"
        "${GLM_INCLUDE_DIRS}"
)

target_link_libraries(
        OpenGL-PBR PUBLIC
        "${GLEW_LIBRARIES}"
        "${GLFW_LIBRARIES}"
        "${OPENGL_LIBRARIES}"
)

