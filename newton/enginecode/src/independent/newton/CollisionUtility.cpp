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
            vector2 normal = delta / distance;
            float combinedRestitution = std::min(a.getRigidBody().material.restitution, b.getRigidBody().material.restitution);
            float totalInvMass = a.getRigidBody().getInvMass() + b.getRigidBody().getInvMass();

            // Relative velocity
            vector2 relativeVelocity = a.getRigidBody().getVelocity() - b.getRigidBody().getVelocity();

            // Velocity along the normal
            float velocityAlongNormal = vector2::dotProduct(relativeVelocity, normal);

            // Do not resolve if objects are separating
            if (velocityAlongNormal > 0) return;

            // Calculate impulse scalar
            float impulseScalar = -(1 + combinedRestitution) * velocityAlongNormal;
            impulseScalar /= totalInvMass;

            // Apply impulse
            vector2 impulse = normal * impulseScalar;
            a.getRigidBody().applyImpulse(impulse * a.getRigidBody().getInvMass());
            b.getRigidBody().applyImpulse(impulse.invert() * b.getRigidBody().getInvMass());

            // Positional correction
            const float percent = 0.2f; // usually 20% to 80%
            const float slop = 0.01f; // usually 0.01 to 0.1
            float penetrationAmount = std::max(penetrationDepth - slop, 0.0f);
            vector2 correctionDirection = normal * (penetrationAmount / totalInvMass);
            vector2 correction = correctionDirection * percent;
            a.getRigidBody().setPosition(a.getRigidBody().getPosition() + correction * a.getRigidBody().getInvMass());
            b.getRigidBody().setPosition(b.getRigidBody().getPosition() - correction * b.getRigidBody().getInvMass());
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
        float distance = sqrt(diff.x * diff.x + diff.y * diff.y);

        if (distance < circle.getRadius()) {
            vector2 normal = diff / distance;
            float penetrationDepth = circle.getRadius() - distance;
            float combinedRestitution = std::min(circle.getRigidBody().material.restitution, obb.getRigidBody().material.restitution);
            float totalInvMass = circle.getRigidBody().getInvMass() + obb.getRigidBody().getInvMass();

            // Relative velocity
            vector2 relativeVelocity = circle.getRigidBody().getVelocity();
            if (obb.getRigidBody().isDynamic()) {
                relativeVelocity -= obb.getRigidBody().getVelocity();
            }

            // Velocity along the normal
            float velocityAlongNormal = vector2::dotProduct(relativeVelocity, normal);

            // Do not resolve if objects are separating
            if (velocityAlongNormal > 0) return;

            // Calculate impulse scalar
            float impulseScalar = -(1 + combinedRestitution) * velocityAlongNormal;
            impulseScalar /= totalInvMass;

            // Apply impulse
            vector2 impulse = normal * impulseScalar;
            circle.getRigidBody().applyImpulse(impulse * circle.getRigidBody().getInvMass());
            if (obb.getRigidBody().isDynamic()) {
                obb.getRigidBody().applyImpulse(impulse.invert() * obb.getRigidBody().getInvMass());
            }

            // Positional correction
            const float percent = 0.2f;
            const float slop = 0.01f;
            float penetrationAmount = std::max(penetrationDepth - slop, 0.0f);
            vector2 correctionDirection = normal * (penetrationAmount / totalInvMass);
            vector2 correction = correctionDirection * percent;
            circle.getRigidBody().setPosition(circle.getRigidBody().getPosition() + correction * circle.getRigidBody().getInvMass());
            if (obb.getRigidBody().isDynamic()) {
                obb.getRigidBody().setPosition(obb.getRigidBody().getPosition() - correction * obb.getRigidBody().getInvMass());
            }
        }
    }


    void CollisionUtility::resolveCollision(OBB& a, OBB& b)
    {
        vector2 delta = a.getCenter() - b.getCenter();
        vector2 overlap;

        overlap.x = a.getExtents().x + b.getExtents().x - abs(delta.x);
        overlap.y = a.getExtents().y + b.getExtents().y - abs(delta.y);

        if (overlap.x > 0 && overlap.y > 0) {
            vector2 normal;
            vector2 penetrationVector;
            if (overlap.x < overlap.y) {
                penetrationVector.x = (delta.x > 0 ? overlap.x : -overlap.x);
                penetrationVector.y = 0;
                normal = vector2(penetrationVector.x > 0 ? 1 : -1, 0);
            }
            else {
                penetrationVector.x = 0;
                penetrationVector.y = (delta.y > 0 ? overlap.y : -overlap.y);
                normal = vector2(0, penetrationVector.y > 0 ? 1 : -1);
            }

            float combinedRestitution = std::min(a.getRigidBody().material.restitution, b.getRigidBody().material.restitution);
            float totalInvMass = a.getRigidBody().getInvMass() + b.getRigidBody().getInvMass();

            // Relative velocity
            vector2 relativeVelocity = a.getRigidBody().getVelocity() - b.getRigidBody().getVelocity();

            // Velocity along the normal
            float velocityAlongNormal = vector2::dotProduct(relativeVelocity, normal);

            // Do not resolve if objects are separating
            if (velocityAlongNormal > 0) return;

            // Calculate impulse scalar
            float impulseScalar = -(1 + combinedRestitution) * velocityAlongNormal;
            impulseScalar /= totalInvMass;

            // Apply impulse
            vector2 impulse = normal * impulseScalar;
            a.getRigidBody().applyImpulse(impulse * a.getRigidBody().getInvMass());
            b.getRigidBody().applyImpulse(impulse.invert() * b.getRigidBody().getInvMass());

            // Positional correction
            const float percent = 0.2f;
            const float slop = 0.01f;
            float penetrationAmount = std::max(std::max(abs(penetrationVector.x), abs(penetrationVector.y)) - slop, 0.0f);
            vector2 correctionDirection = normal * (penetrationAmount / totalInvMass);
            vector2 correction = correctionDirection * percent;
            a.getRigidBody().setPosition(a.getRigidBody().getPosition() + correction * a.getRigidBody().getInvMass());
            b.getRigidBody().setPosition(b.getRigidBody().getPosition() - correction * b.getRigidBody().getInvMass());
        }
    }


    bool CollisionUtility::circleToCircle(const Circle& a, const Circle& b)
    {
        vector2 delta = a.getPosition() - b.getPosition();
        float distanceSquared = delta.x * delta.x + delta.y * delta.y;
        float radiusSum = a.getRadius() + b.getRadius();

        return distanceSquared <= (radiusSum * radiusSum);
    }

    bool CollisionUtility::circleToOBB(const Circle& circle, const OBB& obb)
    {
        vector2 localCirclePos = circle.getPosition() - obb.getCenter();

        float closestX = std::max(-obb.getExtents().x, std::min(localCirclePos.x, obb.getExtents().x));
        float closestY = std::max(-obb.getExtents().y, std::min(localCirclePos.y, obb.getExtents().y));

        vector2 closestPoint(closestX, closestY);
        vector2 diff = localCirclePos - closestPoint;

        return diff.x * diff.x + diff.y * diff.y <= circle.getRadius() * circle.getRadius();
    }

    bool CollisionUtility::OBBToOBB(const OBB& a, const OBB& b)
    {
        if (abs(a.getCenter().x - b.getCenter().x) > (a.getExtents().x + b.getExtents().x)) return false;
        if (abs(a.getCenter().y - b.getCenter().y) > (a.getExtents().y + b.getExtents().y)) return false;

        return true;
    }
}
