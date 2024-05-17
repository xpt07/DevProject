/** \file application.h
 *  @brief Header file for the Application class.
 *  Manages the main loop of the program and interfaces with rendering components.
 */

#pragma once
#include "Gui.h"
#include <memory>
#include <chrono>

namespace Newton {

    class Gui; //!< Forward declaration of Gui class

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
        * @brief Sets the current obbscene.
        * @param scene Unique pointer to the new obbscene.
        */
        void setOBBScene(std::unique_ptr<OBBScene> scene);

        /**
        * @brief Sets the current obbscene.
        * @param scene Unique pointer to the new obbscene.
        */
        void setCircleScene(std::unique_ptr<CircleScene> scene);

        /**
         * @brief Gets the current scene.
         * @return Pointer to the current scene.
         */
        Scene* getScene() const;

        /**
         * @brief Gets the current obbscene.
         * @return Pointer to the current obbscene.
         */
        OBBScene* getOBBScene() const;

        /**
        * @brief Gets the current obbscene.
        * @return Pointer to the current obbscene.
        */
        CircleScene* getCircleScene() const;

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
        std::unique_ptr<OBBScene> m_obbScene; //!< Unique pointer to the current obbscene.
        std::unique_ptr<CircleScene> m_circleScene; //!< Unique pointer to the current circlescene.
        std::unique_ptr<Gui> m_gui; //!< Unique pointer to the GUI interface.
        enum class ActiveScene { None, Scene, OBBScene, CircleScene } activeScene = ActiveScene::None;
    };

    /**
     * @brief Starts the application. Ensures that only one instance is running.
     * @return Pointer to the Application instance.
     */
    Application* startApplication();
}
