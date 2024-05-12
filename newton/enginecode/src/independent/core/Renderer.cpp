#include "engine_pch.h"
#include "core/Renderer.h"
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Newton
{
    Renderer::Renderer(int windowWidth, int windowHeight)
        : windowWidth(windowWidth), windowHeight(windowHeight)
    {
        // Initialize OpenGL or any other necessary setup
        // ...

        // Set up the viewport
        glViewport(0, 0, windowWidth, windowHeight);
    }

    Renderer::~Renderer()
    {
        // Cleanup resources if needed
        // ...
    }

    void Renderer::renderCircle(const Circle& circle)
    {
        // Set up the rendering state for a simple example
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set up an orthographic projection (adjust as needed)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, windowWidth, 0, windowHeight, -1, 1);

        // Set up the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Draw the circle
        glColor3f(1.0f, 0.0f, 0.0f); // Set color to red (adjust as needed)
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i <= 360; ++i)
        {
            float angle = static_cast<float>(i) * 3.14159f / 180.0f;
            float x = circle.getRadius() * std::cos(angle);
            float y = circle.getRadius() * std::sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }
}