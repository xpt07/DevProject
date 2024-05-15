/** \file Gui.h */
#pragma once
#include "core/core.h"
#include "newton/Scene.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Newton
{
    class Scene;

    /**
     * @brief Struct to hold temporary GUI input values.
     */
    struct GuiVals {
        bool circleAdded = false; //!< Flag indicating if a circle is added.
        float circleRadius = 50.0f; //!< Radius of the circle.
        float circlePosX = 500.0f; //!< X-coordinate of the circle.
        float circlePosY = 500.0f; //!< Y-coordinate of the circle.
        bool isStatic = false; //!< Flag indicating if an object is static.
        float obbWidth = 300.0f; //!< Width of the oriented bounding box.
        float obbHeight = 50.0f; //!< Height of the oriented bounding box.
        float obbPosX = 400.0f; //!< X-coordinate of the oriented bounding box.
        float obbPosY = 300.0f; //!< Y-coordinate of the oriented bounding box.
    };

    /**
     * @brief Class for managing GUI rendering and interaction.
     */
    class Gui {
    public:
        /**
         * @brief Constructor.
         * @param window Pointer to the GLFW window.
         * @param scene Reference to the Scene instance.
         */
        Gui(GLFWwindow* window, Scene& scene);

        /**
         * @brief Destructor.
         */
        ~Gui();

        /**
         * @brief Begins the GUI rendering process.
         */
        void beginRender();

        /**
         * @brief Renders the GUI.
         */
        void render();

        /**
         * @brief Draws custom GUI elements.
         */
        void drawCustomGui();

    private:
        GLFWwindow* m_window; //!< Pointer to the GLFW window.
        GuiVals guiVals; //!< Structure holding temporary GUI input values.
        Scene& m_scene; //!< Reference to the Scene instance.
    };
}