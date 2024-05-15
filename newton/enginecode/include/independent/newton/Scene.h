/** \file Scene.h */
#pragma once
#include <vector>
#include "RigidBody.h"
#include "newton/CollisionUtility.h"
#include "newton/Shape/Circle.h"
#include "newton/Shape/OBB.h"

namespace Newton
{
    /**
     * @brief Class representing a 2D scene with dynamic and static objects.
     */
    class Scene
    {
    public:
        /**
         * @brief Default constructor.
         */
        Scene();

        /**
         * @brief Destructor.
         */
        ~Scene() {};

        /**
         * @brief Add a circle to the scene.
         * @param circle The circle to add.
         */
        void addCircle(const Circle& circle);

        /**
         * @brief Add an OBB to the scene.
         * @param obb The OBB to add.
         */
        void addOBB(const OBB& obb);

        /**
         * @brief Update the scene.
         * @param timestep The time step for the update.
         */
        void onUpdate(float timestep);

        /**
         * @brief Check collisions between objects in the scene.
         */
        void checkCollisions();

        /**
         * @brief Draw the scene.
         */
        void onDraw();

    private:
        std::vector<Circle> m_circles; //!< Vector containing circles in the scene.
        std::vector<OBB> m_OBBs; //!< Vector containing OBBs in the scene.
    };
}
