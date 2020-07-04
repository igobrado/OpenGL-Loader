list(APPEND OPENGL_PBR_HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/ImGuiAbstraction/ImGuiAbstraction.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/EventSystem/EventDispatcher.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/EventSystem/MoveEvents.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/EventSystem/Event.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/property/DirectionalLight.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/property/Light.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/property/PointLight.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/property/Material.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/common/Logging.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Camera.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/GLError.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Keyboard.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Mesh.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Mouse.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Shader.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Texture.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/Window.hxx"
        )

list(APPEND OPENGL_PBR_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/common/Logging.cxx"
        )
