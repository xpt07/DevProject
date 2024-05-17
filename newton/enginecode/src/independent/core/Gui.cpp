#include "engine_pch.h"
#include "core/Gui.h"

namespace Newton
{
    Gui::Gui(GLFWwindow* window, Scene& scene, OBBScene& obbScene, CircleScene& circleScene)
        : m_window(window), m_scene(scene), m_obbScene(obbScene) , m_circleScene(circleScene){
        ImGui::CreateContext();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 130");
    }

    Gui::~Gui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Gui::render() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();



        // Left sidebar for scene selection
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(200, ImGui::GetIO().DisplaySize.y));
        if (ImGui::Begin("Sidebar", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {
 
            ImGui::Separator();
            ImGui::Text("Preloaded simulation environments:");
            if (ImGui::Button("Scene 1")) {
                Application::getInstance().setScene(std::make_unique<Scene>());
            }
            if (ImGui::Button("OBB Scene")) {
                Application::getInstance().setOBBScene(std::make_unique<OBBScene>());
            }
            if (ImGui::Button("Circle Scene")) {
                Application::getInstance().setCircleScene(std::make_unique<CircleScene>());
            }
        }
        ImGui::End();

        // Right panel for variable changes
        ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 200, 0));
        ImGui::SetNextWindowSize(ImVec2(200, ImGui::GetIO().DisplaySize.y));
        if (ImGui::Begin("Variables to be changed:", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove)) {

            // Add sliders and input fields for variables here
            ImGui::Text("Circle Properties");
            ImGui::SliderFloat("Radius", &guiVals.circleRadius, 1.0f, 100.0f, "%.1f");
            ImGui::SliderFloat("Circle Position X", &guiVals.circlePosX, 0.0f, 800.0f, "%.0f");
            ImGui::SliderFloat("Circle Position Y", &guiVals.circlePosY, 0.0f, 600.0f, "%.0f");
            ImGui::Checkbox("Static", &guiVals.isStatic);
            ImGui::InputFloat("Restitution", &guiVals.circleRestitution, 0.0f, 1.0f, "%.2f");
            ImGui::InputFloat("Friction", &guiVals.circleFriction, 0.0f, 1.0f, "%.2f");
            ImGui::InputFloat("Mass", &guiVals.circleMass, 0.1f, 100.0f, "%.2f");

            ImGui::Text("OBB Properties");
            ImGui::SliderFloat("Width", &guiVals.obbWidth, 10.0f, 500.0f, "%.0f");
            ImGui::SliderFloat("Height", &guiVals.obbHeight, 10.0f, 500.0f, "%.0f");
            ImGui::SliderFloat("OBB Position X", &guiVals.obbPosX, 0.0f, 800.0f, "%.0f");
            ImGui::SliderFloat("OBB Position Y", &guiVals.obbPosY, 0.0f, 600.0f, "%.0f");
            ImGui::Checkbox("Static", &guiVals.isStatic);
            ImGui::InputFloat("OBB Restitution", &guiVals.obbRestitution, 0.0f, 1.0f, "%.2f");
            ImGui::InputFloat("OBB Friction", &guiVals.obbFriction, 0.0f, 1.0f, "%.2f");
            ImGui::InputFloat("OBB Mass", &guiVals.obbMass, 0.1f, 100.0f, "%.2f");
        }
        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}