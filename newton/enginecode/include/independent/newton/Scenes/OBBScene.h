/** \file Gui.h */
#pragma once
#include <vector>
#include "newton/CollisionUtility.h"
#include "newton/Shape/OBB.h"

namespace Newton {

    /**
     * @class OBBScene
     * @brief A scene that contains and manages multiple OBB objects.
     *
     * The OBBScene class handles the initialization, updating, drawing,
     * and collision checking of a set of OBB objects arranged in a specific layout.
     */
    class OBBScene {
    public:
        /**
         * @brief Constructor that initializes the shapes and materials.
         */
        OBBScene();

        /**
         * @brief Updates the scene.
         * @param deltaTime The time elapsed since the last update.
         */
        void onUpdate(float deltaTime);

        /**
         * @brief Renders the scene.
         */
        void onDraw();

    private:
        /**
         * @brief Initializes the default shapes in the scene.
         */
        void initializeShapes();

        /**
         * @brief Sets initial materials for physics bodies.
         */
        void initializeMaterials();

        /**
         * @brief Updates physics bodies based on time step.
         * @param deltaTime The time elapsed since the last update.
         */
        void updateShapes(float deltaTime);

        /**
         * @brief Checks and resolves collisions between OBBs.
         */
        void checkOBBCollisions();

        std::vector<OBB> m_OBBs; //!< Contains all OBBs in the scene.
        float dt; //!< Last frame's delta time.
    };
}
