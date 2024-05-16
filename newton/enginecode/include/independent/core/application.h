/** \file application.h */
#pragma once

#include "newton/Scene.h"
#include "Gui.h"
#include <memory>
#include <chrono>

namespace Newton {

    /**
     * @brief The Application class manages the main loop of the program and handles rendering.
     */
    class Application
    {
    public:
        /**
         * @brief Destructor.
         */
        virtual ~Application();

        /**
         * @brief Gets the instance of the Application singleton.
         * @return Reference to the Application instance.
         */
        inline static Application& getInstance() { return *s_instance; }

        /**
         * @brief Runs the application main loop.
         */
        void run();

        /**
         * @brief Renders the scene.
         */
        void renderScene();

        /**
         * @brief Sets the current scene.
         * @param scene The scene to set.
         */
        void setScene(Scene* scene) { m_scene = scene; }

        /**
         * @brief Gets the current scene.
         * @return Pointer to the current scene.
         */
        Scene* getScene() const { return m_scene; }

    protected:
        /**
         * @brief Constructor.
         */
        Application();

    private:
        double deltaTime; //!< Time elapsed since the last frame.
        static Application* s_instance; //!< Singleton instance of the Application.
        bool m_running = true; //!< Flag indicating whether the application is running.
        Scene* m_scene = nullptr; //!< Pointer to the current scene.
    };

    /**
     * @brief Starts the application.
     * @return Pointer to the Application instance.
     */
    Application* startApplication();
}
