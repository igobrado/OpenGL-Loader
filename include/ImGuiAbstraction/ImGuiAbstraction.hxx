#ifndef OPENGL_PBR_IMGUIABSTRACTION_HXX
#define OPENGL_PBR_IMGUIABSTRACTION_HXX
#include <GL/glew.h>
#include <GLFW/glfw3.h>
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
    ImGuiAbstraction(GLFWwindow* window, std::uint8_t numberOfMeshes)
        : mWindowRef{ window }
        , mColorOfScreen{ 0.0f, 0.0f, 0.0f }
        , mScalingFactors{ numberOfMeshes }
        , mRotateAroundAxises{ true, false, false }
        , mTranslateFactors{ numberOfMeshes }
        , mRotationAngle{ 1.0f }
    {
        for (auto& factor : mScalingFactors)
        {
            factor[0] = 0.4f;
            factor[1] = 0.4f;
            factor[2] = 1.0f;
        }

        for (auto& factor : mTranslateFactors)
        {
            factor[2] = -2.5f;
        }
    }

    ImGuiAbstraction(GLFWwindow* window, const char* glslVersion, std::uint8_t numberOfMeshes)
        : mWindowRef{ window }
        , mColorOfScreen{ 0.0f, 0.0f, 0.0f }
        , mScalingFactors{ numberOfMeshes }
        , mRotateAroundAxises{ true, false, false }
        , mTranslateFactors{ numberOfMeshes }
        , mRotationAngle{ 1.0f }
    {
        for (auto& factor : mScalingFactors)
        {
            factor[0] = 0.4f;
            factor[1] = 0.4f;
            factor[2] = 1.0f;
        }

        for (auto& factor : mTranslateFactors)
        {
            factor[2] = -2.5f;
        }

        initializeImGui(glslVersion);
    }

    const float getRotationAngle() const
    {
        return mRotationAngle;
    }

    glm::vec3 getTranslateFactorVec3(std::uint8_t objectNumber) const
    {
        return glm::vec3(
                mTranslateFactors[objectNumber][0],
                mTranslateFactors[objectNumber][1],
                mTranslateFactors[objectNumber][2]);
    }

    glm::vec3 getRotationRotationFactorVec3() const
    {
        return glm::vec3(mRotateAroundAxises[0], mRotateAroundAxises[1], mRotateAroundAxises[2]);
    }

    glm::vec3 getScalingFactorByAxisVec3(std::uint8_t objectNumber) const
    {
        return glm::vec3(
                mScalingFactors[objectNumber][0],
                mScalingFactors[objectNumber][1],
                mScalingFactors[objectNumber][2]);
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

        ImGui::SliderFloat3("Translate object one", &mTranslateFactors[0][0], -10.0f, 10.0f);
        ImGui::SliderFloat3("Translate object two", &mTranslateFactors[1][0], -10.0f, 10.0f);
        ImGui::SliderFloat3("Scaling XYZ object one", &mScalingFactors[0][0], 0.0f, 1.0f);
        ImGui::SliderFloat3("Scaling XYZ object two", &mScalingFactors[1][0], 0.0f, 1.0f);
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
    std::vector<std::array<float, 3>> mTranslateFactors;
    std::vector<std::array<float, 3>> mScalingFactors;
    std::array<float, 4>              mColorOfScreen;
    std::array<bool, 3>               mRotateAroundAxises;

    float       mRotationAngle;
    GLFWwindow* mWindowRef;
};

}  // namespace gui

#endif  // OPENGL_PBR_IMGUIABSTRACTION_HXX
