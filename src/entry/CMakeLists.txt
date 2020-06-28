list(APPEND OPENGL_PBR_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/main.cxx
        )

add_executable(
        OpenGL-PBR
        "${OPENGL_PBR_HEADERS}"
        "${OPENGL_PBR_SOURCES}"
        "${IMGUI_SRC_DIR}/imgui.cpp"
        "${IMGUI_SRC_DIR}/imgui_draw.cpp"
        "${IMGUI_SRC_DIR}/imgui_widgets.cpp"
        "${IMGUI_EXAMPLES_DIR}/imgui_impl_opengl3.cpp"
        "${IMGUI_EXAMPLES_DIR}/imgui_impl_glfw.cpp"
)

target_compile_definitions(
        OpenGL-PBR PUBLIC
        "IMGUI_IMPL_OPENGL_LOADER_GLEW"
)