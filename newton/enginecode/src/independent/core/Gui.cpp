#include "engine_pch.h"
#include "core/Gui.h"

namespace Newton
{
    Gui::Gui(GLFWwindow* window, Scene& scene)
        : m_window(window), m_scene(scene) {
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

    void Gui::render()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Set the window position to the left side of the screen
        ImGui::SetNextWindowPos(ImVec2(0, 0)); // Positions the window at the top-left corner

        // Set the window size
        ImGui::SetNextWindowSize(ImVec2(300, 600)); // Set the window size to 300px width and 600px height

        if (ImGui::Begin("Physics Properties Editor", nullptr, ImGuiWindowFlags_NoMove))
        {
            if (ImGui::BeginTabBar("Shape Properties"))
            {
                if (ImGui::BeginTabItem("Circle Properties"))
                {
                    ImGui::Text("Geometric Properties");
                    ImGui::SliderFloat("Radius", &guiVals.circleRadius, 1.0f, 100.0f, "%.1f");
                    ImGui::SliderFloat("Position X", &guiVals.circlePosX, 0.0f, 800.0f, "%.0f");
                    ImGui::SliderFloat("Position Y", &guiVals.circlePosY, 0.0f, 600.0f, "%.0f");

                    ImGui::Text("Physical Properties");
                    ImGui::Checkbox("Static", &guiVals.isStatic);
                    ImGui::InputFloat("Restitution", &guiVals.circleRestitution, 0.0f, 1.0f, "%.2f");
                    ImGui::InputFloat("Friction", &guiVals.circleFriction, 0.0f, 1.0f, "%.2f");
                    ImGui::InputFloat("Mass", &guiVals.circleMass, 0.1f, 100.0f, "%.2f");

                    if (ImGui::Button("Add/Update Circle"))
                    {
                        //m_scene.addCircle(guiVals.circleRadius, vector2(guiVals.circlePosX, guiVals.circlePosY), guiVals.isStatic, guiVals.circleRestitution, guiVals.circleFriction, guiVals.circleMass);
                    }
                    ImGui::EndTabItem();
                }

                if (ImGui::BeginTabItem("OBB Properties"))
                {
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

                    if (ImGui::Button("Add/Update OBB"))
                    {
                        /* m_scene.addOBB(guiVals.obbWidth, guiVals.obbHeight, vector2(guiVals.obbPosX, guiVals.obbPosY), guiVals.isStatic, guiVals.obbRestitution, guiVals.obbFriction, guiVals.obbMass);*/
                    }
                    ImGui::EndTabItem();
                }
                ImGui::EndTabBar();
            }

            ImGui::End();
        }

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}