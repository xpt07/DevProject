/** \file application.h
 *  @brief Header file for the Application class.
 *  Manages the main loop of the program and interfaces with rendering components.
 */

#pragma once

#include "newton/Scene.h"
#include "Gui.h"
#include <memory>
#include <chrono>

namespace Newton {

    /**
     * @class Application
     * @brief Manages the main loop of the program and handles rendering.
     *
     * The Application class controls the game loop, manages scenes, and handles rendering through
     * associated GUI components.
     */
    class Application {
    public:
        /**
         * @brief Destructor. Cleans up resources.
         */
        virtual ~Application();

        /**
         * @brief Returns the singleton instance of Application.
         * @return Reference to the Application instance.
         */
        static Application& getInstance();

        /**
         * @brief Starts the application main loop.
         */
        void run();

        /**
         * @brief Renders the scene.
         */
        void renderScene();

        /**
         * @brief Sets the current scene.
         * @param scene Unique pointer to the new scene.
         */
        void setScene(std::unique_ptr<Scene> scene);

        /**
         * @brief Gets the current scene.
         * @return Pointer to the current scene.
         */
        Scene* getScene() const;

    protected:
        /**
         * @brief Constructor. Initializes the application and ensures a single instance.
         */
        Application();

    private:
        double deltaTime; //!< Time elapsed since the last frame.
        static Application* s_instance; //!< Singleton instance of the Application.
        bool m_running = true; //!< Flag indicating whether the application is running.
        std::unique_ptr<Scene> m_scene; //!< Unique pointer to the current scene.
        std::unique_ptr<Gui> gui; //!< Unique pointer to the GUI interface.
    };

    /**
     * @brief Starts the application. Ensures that only one instance is running.
     * @return Pointer to the Application instance.
     */
    Application* startApplication();
}
