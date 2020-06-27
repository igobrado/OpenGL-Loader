list(APPEND OPENGL_PBR_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/Mesh.cxx
        ${CMAKE_CURRENT_LIST_DIR}/Shader.cxx
        )

include ("${CMAKE_CURRENT_LIST_DIR}/entry/CMakeLists.txt")