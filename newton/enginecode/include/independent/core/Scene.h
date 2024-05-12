#pragma once

#include "RigidBody.h"
#include "Renderer.h"
#include "newton/Shape/Circle.h"
#include "newton/Shape/OBB.h"

namespace Newton
{
    /**
     * @brief Class representing a 2D scene with dynamic and static objects.
     */
    class Scene
    {
    public:
        /**
         * @brief Constructor for the scene.
         * @param rendererWidth The width of the renderer window.
         * @param rendererHeight The height of the renderer window.
         */
        Scene(int rendererWidth, int rendererHeight)
            : renderer(rendererWidth, rendererHeight),
            dynamicRigidBody(Circle(vector2(50.0f, 50.0f), 20.0f), vector2(50.0f, 50.0f), vector2(50.0f, 0.0f)),
            staticRigidBody(OBB(vector2(150.0f, 150.0f), vector2(30.0f, 30.0f), 0.0f))
        {}


        /**
         * @brief Run the main loop for the scene.
         */
        void run()
        {
            while (!renderer.shouldClose())
            {
                // Apply a force to the dynamic circle (for demonstration purposes)
                dynamicRigidBody.applyForce(vector2(0.0f, -100.0f));

                // Update the rigid bodies
                dynamicRigidBody.update(0.02f); // Assuming a fixed time step for simplicity
                staticRigidBody.update(0.02f);

                // Render the scene
                renderScene();

                // Swap buffers and poll events
                renderer.swapBuffers();
            }
        }

    private:
        Renderer renderer;          //!< Renderer for the scene.
        RigidBody dynamicRigidBody; //!< Dynamic circle in the scene.
        RigidBody staticRigidBody;  //!< Static OBB (cube) in the scene.

        /**
         * @brief Render the scene.
         */
        void renderScene() const
        {
            // Clear the screen
            glClear(GL_COLOR_BUFFER_BIT);

            // Render the dynamic circle
            renderer.render(dynamicRigidBody);

            // Render the static OBB
            renderer.render(staticRigidBody);
        }
    };
}
