list(APPEND OPENGL_PBR_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/main.cxx
        )
add_executable(
        OpenGL-PBR
        "${OPENGL_PBR_SOURCES}"
        "${OPENGL_PBR_SOURCES}"
)