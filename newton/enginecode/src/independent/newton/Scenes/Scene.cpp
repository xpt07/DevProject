#include "engine_pch.h"
#include "newton/Scenes/Scene.h"

namespace Newton {

    Scene::Scene() {
        initializeShapes();
        initializeMaterials();
    }

    void Scene::initializeShapes() {
        // Add circles with initial positions and types
        m_circles.emplace_back(50.0, vector2(650.0, 600.0), RigidBodyType::Dynamic);
        m_circles.emplace_back(50.0, vector2(510.0, 300.0));

        // Add OBBs with initial positions, sizes, and types
        m_OBBs.emplace_back(vector2(500.0, 50.0), vector2(300.0, 30.0));
        m_OBBs.emplace_back(vector2(700.0, 200.0), vector2(30.0, 100.0), RigidBodyType::Static);
        m_OBBs.emplace_back(vector2(400.0, 150.0), vector2(30.0, 30.0), RigidBodyType::Dynamic);
    }

    void Scene::initializeMaterials() {
        Material circleMat(2.0f, 2.0f, 0.5f);
        for (auto& circle : m_circles) {
            circle.setMaterialProperties(circleMat);
        }

        Material obbMat(2.0f, 2.0f, 0.0f);
        for (auto& obb : m_OBBs) {
            obb.setMaterialProperties(obbMat);
        }
        // Apply initial impulse to a specific OBB
        m_OBBs[2].rigidBody.applyImpulse(vector2(20.0, 0.0));
    }

    void Scene::addCircle(double radius, const vector2& position) {
        m_circles.emplace_back(radius, position);
    }

    void Scene::addOBB(const OBB& obb) {
        m_OBBs.push_back(obb);
    }

    void Scene::onUpdate(float deltaTime) {
        updateShapes(deltaTime);
        checkCollisions();
    }

    void Scene::updateShapes(float deltaTime) {
        for (auto& circle : m_circles) {
            circle.update(deltaTime);
        }

        for (auto& obb : m_OBBs) {
            obb.update(deltaTime);
        }
    }

    void Scene::checkCollisions() {
        checkCircleCollisions();
        checkCircleOBBCollisions();
        checkOBBCollisions();
    }

    void Scene::checkCircleCollisions() {
        for (size_t i = 0; i < m_circles.size(); ++i) {
            for (size_t j = i + 1; j < m_circles.size(); ++j) {
                if (CollisionUtility::checkCollision(m_circles[i], m_circles[j])) {
                    CollisionUtility::resolveCollision(m_circles[i], m_circles[j]);
                }
            }
        }
    }

    void Scene::checkCircleOBBCollisions() {
        for (auto& circle : m_circles) {
            for (auto& obb : m_OBBs) {
                if (CollisionUtility::checkCollision(circle, obb)) {
                    CollisionUtility::resolveCollision(circle, obb);
                }
            }
        }
    }

    void Scene::checkOBBCollisions() {
        for (size_t i = 0; i < m_OBBs.size(); ++i) {
            for (size_t j = i + 1; j < m_OBBs.size(); ++j) {
                if (CollisionUtility::checkCollision(m_OBBs[i], m_OBBs[j])) {
                    CollisionUtility::resolveCollision(m_OBBs[i], m_OBBs[j]);
                }
            }
        }
    }

    void Scene::onDraw() {
        for (const auto& circle : m_circles) {
            circle.draw();
        }
        for (const auto& obb : m_OBBs) {
            obb.draw();
        }
    }

}
