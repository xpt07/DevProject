/** \file Scene.h */
#pragma once

#include <vector>
#include "RigidBody.h"
#include "newton/CollisionUtility.h"
#include "newton/Shape/Circle.h"
#include "newton/Shape/OBB.h"

namespace Newton {

    /**
     * @class Scene
     * @brief Represents a 2D scene containing dynamic and static physics objects such as circles and OBBs.
     *
     * The Scene class manages multiple physics objects, updating their states and handling interactions
     * between them through collision detection and resolution.
     */
    class Scene {
    public:
        /**
         * @brief Constructs a new Scene object.
         */
        Scene();

        /**
         * @brief Adds a circle to the scene.
         * @param radius The radius of the circle.
         * @param position The initial position of the circle.
         */
        void addCircle(double radius, const vector2& position);

        /**
         * @brief Adds an Oriented Bounding Box (OBB) to the scene.
         * @param obb The OBB to add.
         */
        void addOBB(const OBB& obb);

        /**
         * @brief Updates the scene for a given time step.
         * @param deltaTime The time step in seconds.
         */
        void onUpdate(float deltaTime);

        /**
         * @brief Draws all objects within the scene.
         */
        void onDraw();

    private:
        void initializeShapes(); //!< Initializes the default shapes in the scene.
        void initializeMaterials(); //!< Sets initial materials for physics bodies.
        void updateShapes(float deltaTime); //!< Updates physics bodies based on time step.
        void checkCollisions(); //!< Checks and resolves collisions between all objects in the scene.

        void checkCircleCollisions(); //!< Checks and resolves collisions between circles.
        void checkCircleOBBCollisions(); //!< Checks and resolves collisions between circles and OBBs.
        void checkOBBCollisions(); //!< Checks and resolves collisions between OBBs.

        std::vector<Circle> m_circles; //!< Contains all circles in the scene.
        std::vector<OBB> m_OBBs; //!< Contains all OBBs in the scene.

        float dt; //!< Last frame's delta time.
    };
}
