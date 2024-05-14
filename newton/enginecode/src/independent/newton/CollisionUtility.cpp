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

    void CollisionUtility::resolveCollision(Circle& a, Circle& b)
    {
        vector2 delta = a.getPosition() - b.getPosition();
        float distance = sqrt(delta.x * delta.x + delta.y * delta.y);
        float penetrationDepth = a.getRadius() + b.getRadius() - distance;

        if (penetrationDepth > 0) {
            // Calculate the response vector
            vector2 responseVector = delta.normalise() * penetrationDepth;

            // Apply the response vector to both circles
            a.getRigidBody().applyForce(responseVector * -0.5f);
            b.getRigidBody().applyForce(responseVector * 0.5f);
        }
    }

    void CollisionUtility::resolveCollision(Circle& circle, OBB& obb)
    {
        vector2 circlePos = circle.getPosition();
        vector2 obbCenter = obb.getCenter();
        vector2 obbExtents = obb.getExtents();

        vector2 localCirclePos = circlePos - obbCenter;
        float closestX = std::max(-obbExtents.x, std::min(localCirclePos.x, obbExtents.x));
        float closestY = std::max(-obbExtents.y, std::min(localCirclePos.y, obbExtents.y));

        vector2 closestPoint(closestX, closestY);
        vector2 diff = localCirclePos - closestPoint;
        float distance = diff.magnitude();

        float penetrationDepth = circle.getRadius() - distance;

        vector2 responseVector = diff.normalise() * penetrationDepth * 1.1;  // Increased multiplier to ensure separation
        circle.getRigidBody().applyForce(vector2(0.0f, 9.8f));  // Apply to circle
        if (obb.getRigidBody().isDynamic()) {
            obb.getRigidBody().applyForce(responseVector.invert() * 0.5f);  // Less force applied to the OBB if dynamic
        }


    }

    void CollisionUtility::resolveCollision(OBB& a, OBB& b)
    {
        vector2 delta = b.getCenter() - a.getCenter();
        vector2 aExtents = a.getExtents();
        vector2 bExtents = b.getExtents();

        // Calculate overlap on the x and y axes
        float overlapX = (aExtents.x + bExtents.x) - std::abs(delta.x);
        float overlapY = (aExtents.y + bExtents.y) - std::abs(delta.y);

        if (overlapX > 0 && overlapY > 0) {
            // Resolve along the axis of least penetration
            if (overlapX < overlapY) {
                // Move along the x-axis
                vector2 responseVector(delta.x > 0 ? overlapX : -overlapX, 0);
                a.applyForce(responseVector * -0.5f);
                b.applyForce(responseVector * 0.5f);
            }
            else {
                // Move along the y-axis
                vector2 responseVector(0, delta.y > 0 ? overlapY : -overlapY);
                a.applyForce(responseVector * -0.5f);
                b.applyForce(responseVector * 0.5f);
            }
        }
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
