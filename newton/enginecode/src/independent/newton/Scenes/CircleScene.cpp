#include "engine_pch.h"
#include "newton/Scenes/CircleScene.h"

namespace Newton{
	CircleScene::CircleScene()
	{
		initializeShapes();
		initializeMaterials();
	}
	void CircleScene::onUpdate(float deltaTime)
	{
		updateShapes(deltaTime);
		checkCircleCollisions();
	}
	void CircleScene::onDraw()
	{
		for (const auto& circle : m_Circles) {
			circle.draw();
		}
	}
	void CircleScene::initializeShapes() {
		const int rows = 5;  // Number of rows in the inverted pyramid
		const float radius = 20.0f;  // Radius of each circle
		const float spacing = 10.0f; // Additional spacing between circles
		const float startX = 400.0f;  // Starting X position (center)
		const float startY = 100.0f;  // Starting Y position (bottom)

		// Create the inverted pyramid
		for (int i = 0; i < rows; ++i) {
			int circlesInRow = i + 1;  // Increasing number of circles per row as you go up
			float offsetX = startX - (circlesInRow - 1) * (radius + spacing);  // Centering circles in each row
			float posY = startY + i * 2 * (radius + spacing);  // Positioning circles vertically

			for (int j = 0; j < circlesInRow; ++j) {
				float posX = offsetX + j * 2 * (radius + spacing);
				m_Circles.emplace_back(radius, vector2(posX, posY));
			}
		}

		// Create 5 rows of smaller dynamic circles at the top of the scene
        const int smallRows = 5; // Number of small rows
        const float smallRadius = 5.0f; // Radius of the smaller circles
        const float smallSpacing = 15.0f; // Spacing for the smaller circles
        const float topY = 500.0f; // Y position for the top row
        const int smallCirclesInRow = 10; // Number of smaller circles in each top row

        for (int r = 0; r < smallRows; ++r) {
            float smallRowY = topY + r * 2 * (smallRadius + smallSpacing); // Y position for each small row
            float smallOffsetX = startX - (smallCirclesInRow - 1) * (smallRadius + smallSpacing) / 2.0f;
            for (int k = 0; k < smallCirclesInRow; ++k) {
                float posX = smallOffsetX + k * (smallRadius + smallSpacing);
                m_Circles.emplace_back(smallRadius, vector2(posX, smallRowY), RigidBodyType::Dynamic);
            }
        }
    }
	
	void CircleScene::initializeMaterials()
	{
		Material circleMat(2.0f, 2.0f, 0.5f);
		for (auto& circle : m_Circles) {
			circle.setMaterialProperties(circleMat);
		}
	}
	void CircleScene::updateShapes(float deltaTime)
	{
		for (auto& circle : m_Circles) {
			circle.update(deltaTime);
		}
	}

	void CircleScene::checkCircleCollisions()
	{
		for (size_t i = 0; i < m_Circles.size(); ++i) {
			for (size_t j = i + 1; j < m_Circles.size(); ++j) {
				if (CollisionUtility::checkCollision(m_Circles[i], m_Circles[j])) {
					CollisionUtility::resolveCollision(m_Circles[i], m_Circles[j]);
				}
			}
		}
	}
}