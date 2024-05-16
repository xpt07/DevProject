/** \file application.cpp
 *  @brief Implementation file for the Application class.
 *  Handles initialization, game loop, and rendering sequences.
 */

#include "engine_pch.h"
#include "core/application.h"
#include "newton/Shape/Circle.h"
#include "newton/Shape/OBB.h"
#include "core/OpenGLWindow.h"

namespace Newton {

    OpenGLWindow& window = OpenGLWindow::getInstance(800, 600, "Newton Game Engine");

    Application* Application::s_instance = nullptr;

    Application::Application() {
        if (s_instance == nullptr) {
            s_instance = this;
            m_scene = std::make_unique<Scene>();
            gui = std::make_unique<Gui>(window.getGLFWwindow(), *m_scene);
        }
        else {
            throw std::runtime_error("Application instance already exists!");
        }
    }

    Application::~Application() {
        // Proper cleanup handled by unique_ptr
    }

    Application& Application::getInstance() {
        if (s_instance == nullptr) {
            throw std::runtime_error("Application instance not initialized!");
        }
        return *s_instance;
    }

    void Application::run() {
        using namespace std::chrono;

        auto lastFrameTime = high_resolution_clock::now();

        while (m_running) {
            auto currentFrameTime = high_resolution_clock::now();
            deltaTime = duration<double, std::chrono::seconds::period>(currentFrameTime - lastFrameTime).count();
            lastFrameTime = currentFrameTime;

            if (m_scene) {
                m_scene->onUpdate(deltaTime);
            }

            renderScene();
        }
    }

    void Application::renderScene() {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (m_scene) {
            m_scene->onDraw();
        }

        gui->render();

        window.swapBuffers();
        window.pollEvents();
    }

    void Application::setScene(std::unique_ptr<Scene> scene) {
        m_scene = std::move(scene);
    }

    Scene* Application::getScene() const {
        return m_scene.get();
    }

}
