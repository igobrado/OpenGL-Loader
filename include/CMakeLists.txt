list(APPEND OPENGL_PBR_HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/common/Logging.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Camera.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Event.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Keyboard.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Mesh.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Mouse.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Shader.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Window.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/ImGuiAbstraction/ImGuiAbstraction.hxx"
        )

list(APPEND OPENGL_PBR_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/common/Logging.cxx"
        )
