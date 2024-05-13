#include "engine_pch.h"
#include "newton/CollisionUtility.h"
#include <cmath>

namespace Newton
{
    bool CollisionUtility::checkCollision(const Circle& a, const Circle& b)
    {
        return circleToCircle(a, b);
    }

    bool CollisionUtility::checkCollision(const Circle& circle, const OBB& obb)
    {
        return circleToOBB(circle, obb);
    }

    bool CollisionUtility::checkCollision(const OBB& a, const OBB& b)
    {
        return OBBToOBB(a, b);
    }

    bool CollisionUtility::circleToCircle(const Circle& a, const Circle& b)
    {
        vector2 delta = a.getPosition() - b.getPosition();
        float distanceSquared = delta.x * delta.x + delta.y * delta.y;
        float radiusSum = a.getRadius() + b.getRadius();
        //std::cout << "Dist^2: " << distanceSquared << ", Radii^2: " << (radiusSum * radiusSum) << std::endl;

        return distanceSquared <= (radiusSum * radiusSum);
    }

    bool CollisionUtility::circleToOBB(const Circle& circle, const OBB& obb) {
        // Transform circle center to OBB local space
        vector2 localCirclePos = circle.getPosition() - obb.getCenter();

        // Get closest point on OBB to the circle center
        float closestX = std::max(-obb.getExtents().x, std::min(localCirclePos.x, obb.getExtents().x));
        float closestY = std::max(-obb.getExtents().y, std::min(localCirclePos.y, obb.getExtents().y));

        // Calculate distance from circle center to this closest point
        vector2 closestPoint(closestX, closestY);
        vector2 diff = localCirclePos - closestPoint;

        // Check if the distance is less than or equal to the circle's radius
        return diff.x * diff.x + diff.y * diff.y <= circle.getRadius() * circle.getRadius();
    }



    bool CollisionUtility::OBBToOBB(const OBB& a, const OBB& b)
    {
        // Check overlap along the x-axis
        if (abs(a.getCenter().x - b.getCenter().x) > (a.getExtents().x + b.getExtents().x)) return false;
        // Check overlap along the y-axis
        if (abs(a.getCenter().y - b.getCenter().y) > (a.getExtents().y + b.getExtents().y)) return false;

        // If no separating axis is found, the OBBs must be intersecting
        return true;
    }
}
