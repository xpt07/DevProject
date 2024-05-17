#include "engine_pch.h"
#include "newton/Scenes/OBBScene.h"

namespace Newton
{
    OBBScene::OBBScene() {
        initializeShapes();
        initializeMaterials();
    }

    void OBBScene::initializeShapes() {

        // Add OBBs with initial positions, sizes, and types
        m_OBBs.emplace_back(vector2(500.0, 50.0), vector2(300.0, 30.0));
        m_OBBs.emplace_back(vector2(700.0, 200.0), vector2(30.0, 100.0), RigidBodyType::Static);
        m_OBBs.emplace_back(vector2(400.0, 100.0), vector2(30.0, 30.0), RigidBodyType::Dynamic);
        m_OBBs.emplace_back(vector2(500.0, 100.0), vector2(30.0, 30.0), RigidBodyType::Dynamic);
    }

    void OBBScene::initializeMaterials() {

        Material obbMat(2.0f, 2.0f, 0.0f);
        for (auto& obb : m_OBBs) {
            obb.setMaterialProperties(obbMat);
        }
        // Apply initial impulse to a specific OBB
        m_OBBs[2].rigidBody.applyImpulse(vector2(80.0, 0.0));

    }


    void OBBScene::onUpdate(float deltaTime) {
        updateShapes(deltaTime);
        checkOBBCollisions();
    }

    void OBBScene::updateShapes(float deltaTime) {

        for (auto& obb : m_OBBs) {
            obb.update(deltaTime);
        }
        std::cout << m_OBBs[2].rigidBody.getVelocity().x << ", " << m_OBBs[2].rigidBody.getVelocity().y << std::endl;
    }

    void OBBScene::checkOBBCollisions() {
        for (size_t i = 0; i < m_OBBs.size(); ++i) {
            for (size_t j = i + 1; j < m_OBBs.size(); ++j) {
                if (CollisionUtility::checkCollision(m_OBBs[i], m_OBBs[j])) {
                    CollisionUtility::resolveCollision(m_OBBs[i], m_OBBs[j]);
                }
            }
        }
    }

    void OBBScene::onDraw() {
        for (const auto& obb : m_OBBs) {
            obb.draw();
        }
    }
}