#include "engine_pch.h"
#include "core/Gui.h"

namespace Newton
{
    Gui::Gui(GLFWwindow* window, Scene& scene, OBBScene& obbScene)
        : m_window(window), m_scene(scene), m_obbScene(obbScene) {
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

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(300, 600));

        if (ImGui::Begin("Physics Properties Editor", nullptr, ImGuiWindowFlags_NoMove)) {
            if (ImGui::BeginTabBar("Shape Properties")) {
                if (ImGui::BeginTabItem("Circle Properties")) {
                    ImGui::Text("Geometric Properties");
                    ImGui::SliderFloat("Radius", &guiVals.circleRadius, 1.0f, 100.0f, "%.1f");
                    ImGui::SliderFloat("Position X", &guiVals.circlePosX, 0.0f, 800.0f, "%.0f");
                    ImGui::SliderFloat("Position Y", &guiVals.circlePosY, 0.0f, 600.0f, "%.0f");

                    ImGui::Text("Physical Properties");
                    ImGui::Checkbox("Static", &guiVals.isStatic);
                    ImGui::InputFloat("Restitution", &guiVals.circleRestitution, 0.0f, 1.0f, "%.2f");
                    ImGui::InputFloat("Friction", &guiVals.circleFriction, 0.0f, 1.0f, "%.2f");
                    ImGui::InputFloat("Mass", &guiVals.circleMass, 0.1f, 100.0f, "%.2f");

                    if (ImGui::Button("Add/Update Circle")) {
                        // Add or update circle logic
                    }
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("OBB Properties")) {
                    ImGui::Text("Geometric Properties");
                    ImGui::SliderFloat("Width", &guiVals.obbWidth, 10.0f, 500.0f, "%.0f");
                    ImGui::SliderFloat("Height", &guiVals.obbHeight, 10.0f, 500.0f, "%.0f");
                    ImGui::SliderFloat("Position X", &guiVals.obbPosX, 0.0f, 800.0f, "%.0f");
                    ImGui::SliderFloat("Position Y", &guiVals.obbPosY, 0.0f, 600.0f, "%.0f");

                    ImGui::Text("Physical Properties");
                    ImGui::Checkbox("Static", &guiVals.isStatic);
                    ImGui::InputFloat("OBB Restitution", &guiVals.obbRestitution, 0.0f, 1.0f, "%.2f");
                    ImGui::InputFloat("OBB Friction", &guiVals.obbFriction, 0.0f, 1.0f, "%.2f");
                    ImGui::InputFloat("OBB Mass", &guiVals.obbMass, 0.1f, 100.0f, "%.2f");

                    if (ImGui::Button("Add/Update OBB")) {
                        // Add or update OBB logic
                    }
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }

            ImGui::Separator();
            ImGui::Text("Scene Management");
            if (ImGui::Button("Switch to Scene")) {
                Application::getInstance().setScene(std::make_unique<Scene>());
            }
            if (ImGui::Button("Switch to OBB Scene")) {
                Application::getInstance().setOBBScene(std::make_unique<OBBScene>());
            }

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}