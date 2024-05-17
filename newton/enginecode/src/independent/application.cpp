/** \file application.cpp
 *  @brief Implementation file for the Application class.
 *  Handles initialization, game loop, and rendering sequences.
 */

#include "engine_pch.h"
#include "newton/Scenes/Scene.h"
#include "newton/Scenes/OBBScene.h"
#include "core/OpenGLWindow.h"
#include "core/application.h"

namespace Newton {

    OpenGLWindow& window = OpenGLWindow::getInstance(800, 600, "Newton Game Engine");

    Application* Application::s_instance = nullptr;

    Application::Application() {
        if (s_instance == nullptr) {
            s_instance = this;
            m_scene = std::make_unique<Scene>();
            m_obbScene = std::make_unique<OBBScene>();
            m_circleScene = std::make_unique<CircleScene>();
            m_gui = std::make_unique<Gui>(window.getGLFWwindow(), *m_scene, *m_obbScene, *m_circleScene);
            activeScene = ActiveScene::Scene;
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

            switch (activeScene) {
            case ActiveScene::Scene:
                if (m_scene) {
                    m_scene->onUpdate(deltaTime);
                }
                break;
            case ActiveScene::OBBScene:
                if (m_obbScene) {
                    m_obbScene->onUpdate(deltaTime);
                }
                break;
            case ActiveScene::CircleScene:
                if (m_circleScene) {
                    m_circleScene->onUpdate(deltaTime);
                }
                break;
            default:
                break;
            }

            renderScene();
        }
    }

    void Application::renderScene() {
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        switch (activeScene) {
        case ActiveScene::Scene:
            if (m_scene) {
                m_scene->onDraw();
            }
            break;
        case ActiveScene::OBBScene:
            if (m_obbScene) {
                m_obbScene->onDraw();
            }
            break;
        case ActiveScene::CircleScene:
            if (m_circleScene) {
                m_circleScene->onDraw();
            }
            break;
        default:
            break;
        }

        m_gui->render();

        window.swapBuffers();
        window.pollEvents();
    }

    void Application::setScene(std::unique_ptr<Scene> scene) {
        m_scene = std::move(scene);
        activeScene = ActiveScene::Scene;
    }

    void Application::setOBBScene(std::unique_ptr<OBBScene> scene)
    {
        m_obbScene = std::move(scene);
        activeScene = ActiveScene::OBBScene;
    }

    void Application::setCircleScene(std::unique_ptr<CircleScene> scene)
    {
        m_circleScene = std::move(scene);
        activeScene = ActiveScene::CircleScene;
    }

    Scene* Application::getScene() const {
        return m_scene.get();
    }

    OBBScene* Application::getOBBScene() const {
        return m_obbScene.get();
    }

    CircleScene* Application::getCircleScene() const
    {
        return m_circleScene.get();
    }

}
