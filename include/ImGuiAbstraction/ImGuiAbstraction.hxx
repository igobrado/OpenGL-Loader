#ifndef OPENGL_PBR_IMGUIABSTRACTION_HXX
#define OPENGL_PBR_IMGUIABSTRACTION_HXX
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>
#include <imgui.h>

#include <array>
#include <glm/glm.hpp>

namespace gui
{

class ImGuiAbstraction
{
public:
    ImGuiAbstraction(GLFWwindow* window)
        : mWindowRef{ window }
        , mColorOfScreen{ 0.0f, 0.0f, 0.0f }
        , mScalingFactorAxis{ 0.4f, 0.4f, 1.0f }
        , mRotateAroundAxises{ true, false, false }
        , mTranslateFactorAxises{0.0f, 0.0f, -2.5f}
        , mRotationAngle{ 1.0f }
    {
    }

    ImGuiAbstraction(GLFWwindow* window, const char* glslVersion)
        : mWindowRef{ window }
        , mColorOfScreen{ 0.0f, 0.0f, 0.0f }
        , mScalingFactorAxis{ 0.4f, 0.4f, 1.0f }
        , mRotateAroundAxises{ true, false, false }

        , mTranslateFactorAxises{0.0f, 0.0f, -2.5f}
        , mRotationAngle{ 1.0f }
    {
        initializeImGui(glslVersion);
    }

    const float getRotationAngle() const
    {
        return mRotationAngle;
    }

    glm::vec3 getTranslagteFactorVec3() const
    {
        return glm::vec3(mTranslateFactorAxises[0], mTranslateFactorAxises[1], mTranslateFactorAxises[2]);
    }

    glm::vec3 getRotationRotationFactorVec3() const
    {
        return glm::vec3(mRotateAroundAxises[0], mRotateAroundAxises[1], mRotateAroundAxises[2]);
    }

    glm::vec3 getScalingFactorByAxisVec3() const
    {
        return glm::vec3(mScalingFactorAxis[0], mScalingFactorAxis[1], mScalingFactorAxis[2]);
    }

    const std::array<float, 4>& getScreenColor() const
    {
        return mColorOfScreen;
    }

    void initializeImGui(const char* glslVersion)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGuiIO& io = ImGui::GetIO();
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;  // Enable Multi-Viewport
        ImGui_ImplGlfw_InitForOpenGL(mWindowRef, true);
        ImGui_ImplOpenGL3_Init(glslVersion);
    }

    void renderGui()
    {
        StartEndImGuiFrame startEndImGuiFrame{};
        ImGui::ColorEdit4("Color of screen", mColorOfScreen.data());
        ImGui::SliderFloat("Rotation angle", &mRotationAngle, 0.0f, 360.0f);

        ImGui::Checkbox("Rotate around X axis", &mRotateAroundAxises[0]);
        ImGui::Checkbox("Rotate around Y axis", &mRotateAroundAxises[1]);
        ImGui::Checkbox("Rotate around Z axis", &mRotateAroundAxises[2]);


        ImGui::SliderFloat("Translate X axis", &mTranslateFactorAxises[0], -10.0f, 10.0f);
        ImGui::SliderFloat("Translate Y axis", &mTranslateFactorAxises[1], -10.0f, 10.0f);
        ImGui::SliderFloat("Translate Z axis", &mTranslateFactorAxises[2], -10.0f, 10.0f);

        ImGui::SliderFloat("Scaling X", &mScalingFactorAxis[0], 0.0f, 1.0f);
        ImGui::SliderFloat("Scaling Y", &mScalingFactorAxis[1], 0.0f, 1.0f);
        ImGui::SliderFloat("Scaling Z", &mScalingFactorAxis[2], 0.0f, 1.0f);
    }

protected:
    struct StartEndImGuiFrame
    {
        StartEndImGuiFrame()
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();
        }

        ~StartEndImGuiFrame()
        {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            // Render if docking
            ImGuiIO& io = ImGui::GetIO();
            if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
            {
                GLFWwindow* backup_current_context = glfwGetCurrentContext();
                ImGui::UpdatePlatformWindows();
                ImGui::RenderPlatformWindowsDefault();
                glfwMakeContextCurrent(backup_current_context);
            }
        }
    };

private:
    std::array<float, 4> mColorOfScreen;
    std::array<float, 3> mScalingFactorAxis;
    std::array<float, 3> mTranslateFactorAxises;
    std::array<bool, 3>  mRotateAroundAxises;

    float       mRotationAngle;
    GLFWwindow* mWindowRef;
};

}  // namespace gui

#endif  // OPENGL_PBR_IMGUIABSTRACTION_HXX
