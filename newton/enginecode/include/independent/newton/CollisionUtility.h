#pragma once
#include <vector>
#include "newton/Shape/Circle.h"
#include "newton/Shape/OBB.h"

namespace Newton
{
    class CollisionUtility
    {
    public:
        // Collision detection between two circles
        static bool checkCollision(const Circle& a, const Circle& b);

        // Collision detection between a circle and an OBB
        static bool checkCollision(const Circle& circle, const OBB& obb);

        // Collision detection between two OBBs
        static bool checkCollision(const OBB& a, const OBB& b);

        static void resolveCollision(Circle& a, Circle& b);
        static void resolveCollision(Circle& circle, OBB& obb);
        static void resolveCollision(OBB& a, OBB& b);

    private:
        // Utility functions for specific collision checks
        static bool circleToCircle(const Circle& a, const Circle& b);
        static bool circleToOBB(const Circle& circle, const OBB& obb);
        static bool OBBToOBB(const OBB& a, const OBB& b);
    };
}
