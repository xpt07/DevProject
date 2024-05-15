#include "engine_pch.h"
#include "newton/Scene.h"

namespace Newton 
{
	Scene::Scene()
	{
		m_circles.push_back(Circle(50.0, vector2(500.0, 500.0), RigidBodyType::Dynamic));
		m_circles.push_back(Circle(50.0, vector2(510.0, 300.0)));

        Material circleMat(2.0f, 2.0f, 0.5f);
        for (int i = 0; i < m_circles.size(); i++) {
            m_circles[i].setMaterialProperties(circleMat);

        }

        m_OBBs.push_back(OBB(vector2(400.0, 50.0), vector2(300.0, 30.0)));
        m_OBBs.push_back(OBB(vector2(300.0, 500.0), vector2(30.0, 30.0), RigidBodyType::Dynamic));

        Material obbMat(2.0f, 2.0f, 0.3f);
        for (int i = 0; i < m_OBBs.size(); i++) {
            m_OBBs[i].setMaterialProperties(obbMat);
        }
    
	}

    void Scene::addCircle(const Circle& circle)
    {
        m_circles.push_back(circle);
    }

    void Scene::addOBB(const OBB& obb)
    {
        m_OBBs.push_back(obb);
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

    void Scene::checkCollisions()
    {

        for (size_t i = 0; i < m_circles.size(); i++) {
            for (size_t j = i + 1; j < m_circles.size(); j++) {
                if (CollisionUtility::checkCollision(m_circles[i], m_circles[j])) {
                    CollisionUtility::resolveCollision(m_circles[i], m_circles[j]);
                }
            }
        }

        for (size_t i = 0; i < m_circles.size(); i++) {
            for (size_t j = 0; j < m_OBBs.size(); j++) {
                if (CollisionUtility::checkCollision(m_circles[i], m_OBBs[j])) {
                    CollisionUtility::resolveCollision(m_circles[i], m_OBBs[j]);
                }
            }
        }

        for (size_t i = 0; i < m_OBBs.size(); i++) {
            for (size_t j = i + 1; j < m_OBBs.size(); j++) {
                if (CollisionUtility::checkCollision(m_OBBs[i], m_OBBs[j])) {
                    std::cout << "Collision detected between OBB " << i << " and OBB " << j << "!" << std::endl;
                    CollisionUtility::resolveCollision(m_OBBs[i], m_OBBs[j]); // Resolve the collision
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
