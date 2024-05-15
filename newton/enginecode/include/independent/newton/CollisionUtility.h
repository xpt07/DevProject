/** \file CollisionUtility.h */
#pragma once
#include <vector>
#include "newton/Shape/Circle.h"
#include "newton/Shape/OBB.h"

namespace Newton
{
    /**
     * @brief Utility class for collision detection and resolution.
     */
    class CollisionUtility
    {
    public:

        /**
         * @brief Checks collision between two circles.
         * @param a The first circle.
         * @param b The second circle.
         * @return True if there is a collision, false otherwise.
         */
        static bool checkCollision(const Circle& a, const Circle& b);

        /**
         * @brief Checks collision between a circle and an OBB.
         * @param circle The circle.
         * @param obb The OBB.
         * @return True if there is a collision, false otherwise.
         */
        static bool checkCollision(const Circle& circle, const OBB& obb);

        /**
         * @brief Checks collision between two OBBs.
         * @param a The first OBB.
         * @param b The second OBB.
         * @return True if there is a collision, false otherwise.
         */
        static bool checkCollision(const OBB& a, const OBB& b);

        /**
         * @brief Resolves collision between two circles.
         * @param a The first circle.
         * @param b The second circle.
         */
        static void resolveCollision(Circle& a, Circle& b);

        /**
         * @brief Resolves collision between a circle and an OBB.
         * @param circle The circle.
         * @param obb The OBB.
         */
        static void resolveCollision(Circle& circle, OBB& obb);

        /**
         * @brief Resolves collision between two OBBs.
         * @param a The first OBB.
         * @param b The second OBB.
         */
        static void resolveCollision(OBB& a, OBB& b);

    private:
        /**
         * @brief Checks collision between two circles.
         * @param a The first circle.
         * @param b The second circle.
         * @return True if there is a collision, false otherwise.
         */
        static bool circleToCircle(const Circle& a, const Circle& b);

        /**
         * @brief Checks collision between a circle and an OBB.
         * @param circle The circle.
         * @param obb The OBB.
         * @return True if there is a collision, false otherwise.
         */
        static bool circleToOBB(const Circle& circle, const OBB& obb);

        /**
         * @brief Checks collision between two OBBs.
         * @param a The first OBB.
         * @param b The second OBB.
         * @return True if there is a collision, false otherwise.
         */
        static bool OBBToOBB(const OBB& a, const OBB& b);
    };
}
