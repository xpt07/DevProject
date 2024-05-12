#include "engine_pch.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "newton/Shape/Circle.h"

namespace Newton 
{
	void Circle::draw() const
	{
        // Set up the rendering state for a simple example
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Set up an orthographic projection (adjust as needed)
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0, 800, 0, 600, -1, 1);

        // Set up the modelview matrix
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        // Translate the modelview matrix to the circle's position
        glTranslatef(position.x, position.y, 0.0f);

        // Draw the circle
        glColor3f(1.0f, 0.0f, 0.0f); // Set color to red (adjust as needed)
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i <= 360; ++i)
        {
            float angle = static_cast<float>(i) * 3.14159f / 180.0f;
            float xPos = position.x + radius * std::cos(angle);
            float yPos = position.y + radius * std::sin(angle);
            glVertex2f(xPos, yPos);
        }
        glEnd();
	}
}
