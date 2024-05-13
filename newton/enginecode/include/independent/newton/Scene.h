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
        Scene();
        ~Scene() {};

        void onUpdate(float timestep);
        vector2 closestPointOnOBB(const Circle& circle, const OBB& obb);
        void resolveCollision(Circle& c1, Circle& c2);
        void resolveCollision(Circle& circle, OBB& obb);
        void checkCollisions();
        void onDraw();

    private:
        std::vector<Circle> m_circles;
        std::vector<OBB> m_OBBs;
    };
}
