/** \file CircleScene.h */
#pragma once
#include <vector>
#include "newton/CollisionUtility.h"
#include "newton/Shape/Circle.h"

namespace Newton {

    /**
     * @class CircleScene
     * @brief A scene that contains and manages multiple Circle objects.
     *
     * The CircleScene class handles the initialization, updating, drawing,
     * and collision checking of a set of Circle objects arranged in a specific layout.
     */
    class CircleScene {
    public:
        /**
         * @brief Constructor that initializes the shapes and materials.
         */
        CircleScene();

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
         * @brief Checks and resolves collisions between circles.
         */
        void checkCircleCollisions();

        std::vector<Circle> m_Circles; //!< Contains all circles in the scene.
        float dt; //!< Last frame's delta time.
    };
}
