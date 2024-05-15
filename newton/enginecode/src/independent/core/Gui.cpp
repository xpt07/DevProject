#include "engine_pch.h"
#include "core/Gui.h"
#include "newton/Scene.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/common.hpp>


namespace Newton
{
    Gui::Gui(GLFWwindow* window, Scene& scene) :
        m_window(window),
        m_scene(scene)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init();
        ImGui::StyleColorsDark();
    }

    Gui::~Gui()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void Gui::beginRender()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Gui::render()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void Gui::drawCustomGui() {

        ImGui::Begin("Newton");

        if (ImGui::BeginTabBar("Add Shapes to Scene"))
        {
            if (ImGui::BeginTabItem("Add Circle"))
            {
             
                ImGui::InputFloat("Radius", &guiVals.circleRadius);
                ImGui::InputFloat("Position X", &guiVals.circlePosX);
                ImGui::InputFloat("Position Y", &guiVals.circlePosY);
                ImGui::Checkbox("Static", &guiVals.isStatic);
                if (ImGui::Button("Add Circle")) {
                    Circle newCircle(guiVals.circleRadius, vector2(guiVals.circlePosX, guiVals.circlePosY), guiVals.isStatic ? RigidBodyType::Static : RigidBodyType::Dynamic);
                    m_scene.addCircle(newCircle);
                }
                ImGui::EndTabItem();

                ImGui::EndTabItem();
            }

            if (ImGui::BeginTabItem("Add OBB")) {
                
                ImGui::InputFloat("Radius", &guiVals.circleRadius);
                ImGui::InputFloat("Position X", &guiVals.circlePosX);
                ImGui::InputFloat("Position Y", &guiVals.circlePosY);
                ImGui::Checkbox("Static", &guiVals.isStatic);
                if (ImGui::Button("Add Circle")) {
                    Circle newCircle(guiVals.circleRadius, vector2(guiVals.circlePosX, guiVals.circlePosY), guiVals.isStatic ? RigidBodyType::Static : RigidBodyType::Dynamic);
                    m_scene.addCircle(newCircle);
                }
                ImGui::EndTabItem();

                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
      
        ImGui::End();

    }

}