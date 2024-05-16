// OBBScene.h
#pragma once
#include <vector>
#include "newton/CollisionUtility.h"
#include "newton/Shape/OBB.h"

namespace Newton {
    class OBBScene {
    public:
        OBBScene();

        void onUpdate(float deltaTime);

        void onDraw();

    private:
        void initializeShapes(); //!< Initializes the default shapes in the scene.
        void initializeMaterials(); //!< Sets initial materials for physics bodies.
        void updateShapes(float deltaTime); //!< Updates physics bodies based on time step.
        void checkCollisions(); //!< Checks and resolves collisions between all objects in the scene.

        void checkOBBCollisions(); //!< Checks and resolves collisions between OBBs.

        std::vector<OBB> m_OBBs; //!< Contains all OBBs in the scene.

        float dt; //!< Last frame's delta time.

    };
}
