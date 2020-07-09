list(APPEND OPENGL_PBR_SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/application/OpenGLPBR.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/EventSystem/MoveEvents.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/property/DirectionalLight.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/property/Light.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/property/PointLight.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/property/SpotLight.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/property/Material.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/Camera.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/Event.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/Keyboard.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/Mesh.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/Mouse.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/Shader.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/Texture.cxx"
        "${CMAKE_CURRENT_LIST_DIR}/Window.cxx"
        )

list(APPEND OPENGL_PBR_HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/application/IApplication.hxx"
        "${CMAKE_CURRENT_LIST_DIR}/application/OpenGLPBR.hxx"


        )
include ("${CMAKE_CURRENT_LIST_DIR}/entry/CMakeLists.txt")
