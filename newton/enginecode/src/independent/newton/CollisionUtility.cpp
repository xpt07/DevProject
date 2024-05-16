/** \file CollisionUtility.cpp */
#include "engine_pch.h" // Include the precompiled header for the project
#include "newton/CollisionUtility.h" // Include the definition for the CollisionUtility class
#include <cmath> // Include standard library for mathematical operations

// Define the Newton namespace
namespace Newton
{
    /**
    * @brief Utility function to clamp a value within a range.
    * @tparam T Type of the value.
    * @param value The value to clamp.
    * @param min The minimum value.
    * @param max The maximum value.
    * @return The clamped value.
    */
    template<typename T>
    T clamp(T value, T min, T max) { // Template function to ensure the value lies between min and max
        if (value < min) return min; // Return min if value is less than min
        if (value > max) return max; // Return max if value is greater than max
        return value; // Return the value if it's within the range
    }

    // Check if two circles are colliding
    bool CollisionUtility::checkCollision(const Circle& a, const Circle& b)
    {
        return circleToCircle(a, b); // Delegate to the circle-to-circle collision check function
    }

    // Check if a circle and an oriented bounding box (OBB) are colliding
    bool CollisionUtility::checkCollision(const Circle& circle, const OBB& obb)
    {
        return circleToOBB(circle, obb); // Delegate to the circle-to-OBB collision check function
    }

    // Check if two OBBs are colliding
    bool CollisionUtility::checkCollision(const OBB& a, const OBB& b)
    {
        return OBBToOBB(a, b); // Delegate to the OBB-to-OBB collision check function
    }

    // Resolve collision between two circles by adjusting their positions and velocities
    void CollisionUtility::resolveCollision(Circle& a, Circle& b)
    {
        vector2 delta = a.getPosition() - b.getPosition(); // Compute the vector between circle centers
        float distance = sqrt(delta.x * delta.x + delta.y * delta.y); // Calculate the distance between centers
        float penetrationDepth = a.getRadius() + b.getRadius() - distance; // Compute penetration depth

        // Only resolve if circles overlap
        if (penetrationDepth > 0) {
            vector2 normal = delta / distance; // Calculate the collision normal
            float combinedRestitution = std::min(a.getRigidBody().material.restitution, b.getRigidBody().material.restitution); // Calculate the combined restitution
            float combinedFriction = std::sqrt(a.getRigidBody().material.friction * b.getRigidBody().material.friction); // Calculate the combined friction
            float totalInvMass = a.getRigidBody().getInvMass() + b.getRigidBody().getInvMass(); // Sum of the inverse masses

            vector2 relativeVelocity = a.getRigidBody().getVelocity() - b.getRigidBody().getVelocity(); // Calculate relative velocity
            float velocityAlongNormal = vector2::dotProduct(relativeVelocity, normal); // Calculate velocity along the collision normal

            if (velocityAlongNormal > 0) return; // Exit if circles are moving apart

            float impulseScalar = -(1 + combinedRestitution) * velocityAlongNormal; // Calculate impulse scalar
            impulseScalar /= totalInvMass; // Factor in total inverse mass

            vector2 impulse = normal * impulseScalar; // Calculate impulse vector
            a.getRigidBody().applyImpulse(impulse * a.getRigidBody().getInvMass()); // Apply impulse to circle a
            b.getRigidBody().applyImpulse(impulse.invert() * b.getRigidBody().getInvMass()); // Apply impulse to circle b

            vector2 tangent = relativeVelocity - (normal * vector2::dotProduct(relativeVelocity, normal)); // Calculate tangent vector for friction
            if (!(tangent == vector2())) {
                tangent = tangent.normalise(); // Normalize the tangent vector
                float jt = -vector2::dotProduct(relativeVelocity, tangent); // Calculate tangential component of the impulse
                jt /= totalInvMass; // Adjust for mass

                float mu = combinedFriction; // Use combined friction coefficient
                float frictionImpulseScalar = clamp(jt, -impulseScalar * mu, impulseScalar * mu); // Clamp the friction impulse scalar
                vector2 frictionImpulse = tangent * frictionImpulseScalar; // Calculate friction impulse

                a.getRigidBody().applyImpulse(frictionImpulse * a.getRigidBody().getInvMass()); // Apply friction impulse to circle a
                b.getRigidBody().applyImpulse(frictionImpulse.invert() * b.getRigidBody().getInvMass()); // Apply friction impulse to circle b
            }

            const float percent = 0.2f; // Percentage for positional correction
            const float slop = 0.01f; // Allowed penetration margin
            float penetrationAmount = std::max(penetrationDepth - slop, 0.0f); // Calculate corrected penetration
            vector2 correctionDirection = normal * (penetrationAmount / totalInvMass); // Calculate direction for positional correction
            vector2 correction = correctionDirection * percent; // Calculate correction vector
            a.getRigidBody().setPosition(a.getRigidBody().getPosition() + correction * a.getRigidBody().getInvMass()); // Apply positional correction to circle a
            b.getRigidBody().setPosition(b.getRigidBody().getPosition() - correction * b.getRigidBody().getInvMass()); // Apply positional correction to circle b
        }
    }

    // Resolve collision between a circle and an OBB
    void CollisionUtility::resolveCollision(Circle& circle, OBB& obb)
    {
        vector2 circlePos = circle.getPosition(); // Get the circle's position
        vector2 obbCenter = obb.getCenter(); // Get the OBB's center
        vector2 obbExtents = obb.getExtents(); // Get the OBB's extents

        vector2 localCirclePos = circlePos - obbCenter; // Localize circle position relative to OBB
        float closestX = std::max(-obbExtents.x, std::min(localCirclePos.x, obbExtents.x)); // Find the closest X within the OBB bounds
        float closestY = std::max(-obbExtents.y, std::min(localCirclePos.y, obbExtents.y)); // Find the closest Y within the OBB bounds

        vector2 closestPoint(closestX, closestY); // Construct the closest point vector
        vector2 diff = localCirclePos - closestPoint; // Vector from closest point to circle center
        float distance = sqrt(diff.x * diff.x + diff.y * diff.y); // Calculate distance from closest point to circle center

        if (distance < circle.getRadius()) { // Check for collision
            vector2 normal = diff / distance; // Calculate normal of collision
            float penetrationDepth = circle.getRadius() - distance; // Calculate penetration depth

            float combinedRestitution = std::min(circle.getRigidBody().material.restitution, obb.getRigidBody().material.restitution); // Combined restitution
            float combinedFriction = std::sqrt(circle.getRigidBody().material.friction * obb.getRigidBody().material.friction); // Combined friction
            float totalInvMass = circle.getRigidBody().getInvMass() + obb.getRigidBody().getInvMass(); // Total inverse mass

            vector2 relativeVelocity = circle.getRigidBody().getVelocity(); // Relative velocity (circle)
            if (obb.getRigidBody().isDynamic()) {
                relativeVelocity -= obb.getRigidBody().getVelocity(); // Subtract OBB velocity if dynamic
            }

            float velocityAlongNormal = vector2::dotProduct(relativeVelocity, normal); // Velocity component along normal

            if (velocityAlongNormal > 0) return; // Do not resolve if separating

            float impulseScalar = -(1 + combinedRestitution) * velocityAlongNormal; // Calculate impulse scalar
            impulseScalar /= totalInvMass; // Adjust for mass

            vector2 impulse = normal * impulseScalar; // Calculate impulse
            circle.getRigidBody().applyImpulse(impulse * circle.getRigidBody().getInvMass()); // Apply impulse to circle
            if (obb.getRigidBody().isDynamic()) {
                obb.getRigidBody().applyImpulse(impulse.invert() * obb.getRigidBody().getInvMass()); // Apply impulse to OBB if dynamic
            }

            vector2 tangent = relativeVelocity - (normal * vector2::dotProduct(relativeVelocity, normal)); // Calculate tangent for friction
            if (!(tangent == vector2())) {
                tangent = tangent.normalise(); // Normalize tangent vector
                float jt = -vector2::dotProduct(relativeVelocity, tangent); // Calculate tangential component
                jt /= totalInvMass; // Adjust for mass

                float mu = combinedFriction; // Use combined friction
                float frictionImpulseScalar = clamp(jt, -impulseScalar * mu, impulseScalar * mu); // Clamp friction impulse scalar
                vector2 frictionImpulse = tangent * frictionImpulseScalar; // Calculate friction impulse

                circle.getRigidBody().applyImpulse(frictionImpulse * circle.getRigidBody().getInvMass()); // Apply friction impulse to circle
                obb.getRigidBody().applyImpulse(frictionImpulse.invert() * obb.getRigidBody().getInvMass()); // Apply friction impulse to OBB if dynamic
            }

            const float percent = 0.2f; // Percentage for positional correction
            const float slop = 0.01f; // Allowed penetration margin
            float penetrationAmount = std::max(penetrationDepth - slop, 0.0f); // Calculate corrected penetration
            vector2 correctionDirection = normal * (penetrationAmount / totalInvMass); // Calculate direction for positional correction
            vector2 correction = correctionDirection * percent; // Calculate correction vector
            circle.getRigidBody().setPosition(circle.getRigidBody().getPosition() + correction * circle.getRigidBody().getInvMass()); // Apply positional correction to circle
            if (obb.getRigidBody().isDynamic()) {
                obb.getRigidBody().setPosition(obb.getRigidBody().getPosition() - correction * obb.getRigidBody().getInvMass()); // Apply positional correction to OBB if dynamic
            }
        }
    }

    // Resolve collision between two OBBs by adjusting their positions and velocities
    void CollisionUtility::resolveCollision(OBB& a, OBB& b)
    {
        vector2 delta = a.getCenter() - b.getCenter(); // Compute vector between centers
        vector2 overlap; // To hold overlap amounts in x and y directions

        overlap.x = a.getExtents().x + b.getExtents().x - abs(delta.x); // Calculate x-axis overlap
        overlap.y = a.getExtents().y + b.getExtents().y - abs(delta.y); // Calculate y-axis overlap

        if (overlap.x > 0 && overlap.y > 0) { // Check if there is an overlap
            vector2 normal; // To hold the collision normal
            vector2 penetrationVector; // To hold the penetration vector

            if (overlap.x < overlap.y) { // Determine smallest penetration direction
                penetrationVector.x = (delta.x > 0 ? overlap.x : -overlap.x); // Set x penetration
                penetrationVector.y = 0; // No y penetration
                normal = vector2(penetrationVector.x > 0 ? 1 : -1, 0); // Set normal in x
            }
            else {
                penetrationVector.x = 0; // No x penetration
                penetrationVector.y = (delta.y > 0 ? overlap.y : -overlap.y); // Set y penetration
                normal = vector2(0, penetrationVector.y > 0 ? 1 : -1); // Set normal in y
            }

            float combinedRestitution = std::min(a.getRigidBody().material.restitution, b.getRigidBody().material.restitution); // Calculate combined restitution
            float combinedFriction = std::sqrt(a.getRigidBody().material.friction * b.getRigidBody().material.friction); // Calculate combined friction
            float totalInvMass = a.getRigidBody().getInvMass() + b.getRigidBody().getInvMass(); // Total inverse mass

            vector2 relativeVelocity = a.getRigidBody().getVelocity() - b.getRigidBody().getVelocity(); // Calculate relative velocity
            float velocityAlongNormal = vector2::dotProduct(relativeVelocity, normal); // Velocity component along normal

            if (velocityAlongNormal > 0) return; // Do not resolve if separating

            float impulseScalar = -(1 + combinedRestitution) * velocityAlongNormal; // Calculate impulse scalar
            impulseScalar /= totalInvMass; // Adjust for mass

            vector2 impulse = normal * impulseScalar; // Calculate impulse
            a.getRigidBody().applyImpulse(impulse * a.getRigidBody().getInvMass()); // Apply impulse to OBB a
            b.getRigidBody().applyImpulse(impulse.invert() * b.getRigidBody().getInvMass()); // Apply impulse to OBB b

            vector2 tangent = relativeVelocity - (normal * vector2::dotProduct(relativeVelocity, normal)); // Calculate tangent for friction
            if (!(tangent == vector2())) {
                tangent = tangent.normalise(); // Normalize tangent vector
                float jt = -vector2::dotProduct(relativeVelocity, tangent); // Calculate tangential component
                jt /= totalInvMass; // Adjust for mass

                float mu = combinedFriction; // Use combined friction
                float frictionImpulseScalar = clamp(jt, -impulseScalar * mu, impulseScalar * mu); // Clamp friction impulse scalar
                vector2 frictionImpulse = tangent * frictionImpulseScalar; // Calculate friction impulse

                a.getRigidBody().applyImpulse(frictionImpulse * a.getRigidBody().getInvMass()); // Apply friction impulse to OBB a
                b.getRigidBody().applyImpulse(frictionImpulse.invert() * b.getRigidBody().getInvMass()); // Apply friction impulse to OBB b
            }

            const float percent = 0.2f; // Percentage for positional correction
            const float slop = 0.01f; // Allowed penetration margin
            float penetrationAmount = std::max(std::max(abs(penetrationVector.x), abs(penetrationVector.y)) - slop, 0.0f); // Calculate corrected penetration
            vector2 correctionDirection = normal * (penetrationAmount / totalInvMass); // Calculate direction for positional correction
            vector2 correction = correctionDirection * percent; // Calculate correction vector
            a.getRigidBody().setPosition(a.getRigidBody().getPosition() + correction * a.getRigidBody().getInvMass()); // Apply positional correction to OBB a
            b.getRigidBody().setPosition(b.getRigidBody().getPosition() - correction * b.getRigidBody().getInvMass()); // Apply positional correction to OBB b
        }
    }

    // Determine if two circles are colliding by checking the distance against their radii
    bool CollisionUtility::circleToCircle(const Circle& a, const Circle& b)
    {
        vector2 delta = a.getPosition() - b.getPosition(); // Calculate vector between circle centers
        float distanceSquared = delta.x * delta.x + delta.y * delta.y; // Compute squared distance for efficiency
        float radiusSum = a.getRadius() + b.getRadius(); // Sum of the radii

        return distanceSquared <= (radiusSum * radiusSum); // Return true if the distance squared is less than or equal to the squared sum of radii
    }

    // Determine if a circle is colliding with an OBB
    bool CollisionUtility::circleToOBB(const Circle& circle, const OBB& obb)
    {
        vector2 localCirclePos = circle.getPosition() - obb.getCenter(); // Calculate circle position relative to OBB center

        float closestX = std::max(-obb.getExtents().x, std::min(localCirclePos.x, obb.getExtents().x)); // Determine closest X within the OBB bounds
        float closestY = std::max(-obb.getExtents().y, std::min(localCirclePos.y, obb.getExtents().y)); // Determine closest Y within the OBB bounds

        vector2 closestPoint(closestX, closestY); // Construct the closest point vector
        vector2 diff = localCirclePos - closestPoint; // Calculate the difference vector from circle to closest point

        return diff.x * diff.x + diff.y * diff.y <= circle.getRadius() * circle.getRadius(); // Check if the squared distance is less than or equal to the squared radius
    }

    // Determine if two OBBs are colliding by checking projections along their axes
    bool CollisionUtility::OBBToOBB(const OBB& a, const OBB& b)
    {
        // Calculate differences in centers
        if (abs(a.getCenter().x - b.getCenter().x) > (a.getExtents().x + b.getExtents().x)) return false; // Check if they overlap on the x-axis
        if (abs(a.getCenter().y - b.getCenter().y) > (a.getExtents().y + b.getExtents().y)) return false; // Check if they overlap on the y-axis

        return true; // Return true if they overlap on both axes
    }
}
