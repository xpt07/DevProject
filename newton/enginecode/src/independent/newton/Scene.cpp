#include "engine_pch.h"
#include "newton/Scene.h"

namespace Newton 
{
	Scene::Scene()
	{
		m_circles.push_back(Circle(50.0, vector2(500.0, 500.0), vector2(0.0, 0.0)));
		m_circles.push_back(Circle(50.0, vector2(300.0, 500.0), vector2(0.0, 0.0)));

        Material circleMat(1.0f, 0.9f, 0.5f);
        for (int i = 0; i < m_circles.size(); i++) {
            m_circles[i].setMaterialProperties(circleMat);
        }

        m_OBBs.push_back(OBB(vector2(400.0, 50.0), vector2(300.0, 30.0)));

        Material obbMat(2.0f, 0.8f, 0.3f);
        for (int i = 0; i < m_OBBs.size(); i++) {
            m_OBBs[i].setMaterialProperties(obbMat);
        }
	}
    void Scene::onUpdate(float timestep) {
        for (int i = 0; i < m_circles.size(); i++) {
            m_circles[i].update(timestep);
        }

        for (int i = 0; i < m_OBBs.size(); i++) {
            m_OBBs[i].update(timestep);
        }
        checkCollisions();
    }

    vector2 Scene::closestPointOnOBB(const Circle& circle, const OBB& obb)
    {
        vector2 result = obb.getCenter();
        vector2 direction = circle.getPosition() - obb.getCenter();
        float angle = -obb.getRotation() * (PI / 180.0f);  // Convert degrees to radians and rotate in reverse

        direction = direction.rotate(angle);  // Rotate direction to OBB's local space

        vector2 halfExtents = obb.getExtents();
        direction.x = std::max(-halfExtents.x, std::min(halfExtents.x, direction.x));
        direction.y = std::max(-halfExtents.y, std::min(halfExtents.y, direction.y));

        result += direction.rotate(-angle);  // Rotate back to world space
        return result;
    }

    void Scene::resolveCollision(Circle& c1, Circle& c2)
    {
        vector2 relVelocity = c2.getRigidBody().getVelocity() - c1.getRigidBody().getVelocity();
        vector2 normal = c2.getPosition() - c1.getPosition();
        normal.normalise();

        // Calculate relative velocity in terms of the normal direction
        float velAlongNormal = vector2::dotProduct(relVelocity, normal);

        // Do not resolve if velocities are separating
        if (velAlongNormal > 0)
            return;

        // Calculate restitution
        float e = std::min(c1.getRigidBody().material.restitution, c2.getRigidBody().material.restitution);

        // Calculate impulse scalar
        float j = -(1 + e) * velAlongNormal;
        j /= 1 / c1.getRigidBody().material.mass + 1 / c2.getRigidBody().material.mass;

        // Apply impulse
        vector2 impulse = normal * j;
        c1.getRigidBody().applyImpulse(impulse.invert());
        c2.getRigidBody().applyImpulse(impulse);

        // Friction handling (simplified)
        relVelocity = c2.getRigidBody().getVelocity() - c1.getRigidBody().getVelocity(); // Updated relative velocity after normal impulse
        vector2 tangent = relVelocity - (normal * vector2::dotProduct(relVelocity, normal));
        tangent.normalise();

        // Calculate magnitude of the impulse along the tangent
        float jt = -vector2::dotProduct(relVelocity, tangent);
        jt /= 1 / c1.getRigidBody().material.mass + 1 / c2.getRigidBody().material.mass;

        // Pythagorean Solve for friction coefficient
        float mu = sqrt(c1.getRigidBody().material.friction * c2.getRigidBody().material.friction);

        // Clamp magnitude of friction and create friction impulse vector
        vector2 frictionImpulse;
        if (abs(jt) < j * mu)
            frictionImpulse = tangent * jt;
        else
            frictionImpulse = tangent * (-j * mu);

        // Apply friction impulse
        c1.getRigidBody().applyImpulse(frictionImpulse.invert());
        c2.getRigidBody().applyImpulse(frictionImpulse);
    }

    void Scene::resolveCollision(Circle& circle, OBB& obb)
    {
        vector2 pointOnOBB = closestPointOnOBB(circle, obb);
        vector2 normal = circle.getPosition() - pointOnOBB;
        float dist = normal.magnitude();
        normal.normalise();

        // Calculate penetration depth
        float penetrationDepth = circle.getRadius() - dist;
        if (penetrationDepth > 0) {
            vector2 relVelocity = obb.getRigidBody().getVelocity() - circle.getRigidBody().getVelocity();
            float velAlongNormal = vector2::dotProduct(relVelocity, normal);

            // Only resolve if velocities are approaching each other
            if (velAlongNormal < 0) {
                float e = std::min(circle.getRigidBody().material.restitution, obb.getRigidBody().material.restitution);

                // Calculate impulse scalar
                float j = -(1 + e) * velAlongNormal;
                j /= 1 / circle.getRigidBody().material.mass; // Since OBB is static, its reciprocal mass is 0

                // Apply impulse
                vector2 impulse = normal * j;
                circle.getRigidBody().applyImpulse(impulse.invert());


                // Immediate position adjustment to prevent sinking
                circle.getRigidBody().getPosition() += normal * penetrationDepth;
            }
        }
    }

    void Scene::checkCollisions()
    {
        for (size_t i = 0; i < m_circles.size(); i++) {
            for (size_t j = i + 1; j < m_circles.size(); j++) {
                if (CollisionUtility::checkCollision(m_circles[i], m_circles[j])) {
                    std::cout << "Collision detected between Circle " << i << " and Circle " << j << "!" << std::endl;
                    resolveCollision(m_circles[i], m_circles[j]);
                }
            }
        }

        for (Circle& circle : m_circles) {
            for (OBB& obb : m_OBBs) {
                if (CollisionUtility::checkCollision(circle, obb)) {
                    std::cout << "Collision detected between Circle and OBB!" << std::endl;
                    resolveCollision(circle, obb);
                }
            }
        }
    }

    void Scene::onDraw() {
        for (int i = 0; i < m_circles.size(); i++) {
            m_circles[i].draw();
        }

        for (int i = 0; i < m_OBBs.size(); i++) {
            m_OBBs[i].draw();
        }
    }
}
