#include "engine_pch.h"

#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include "newton/Shape/OBB.h"

namespace Newton
{
	void OBB::draw() const
	{
        glPushMatrix(); // Isolate the transformations for this OBB

        // Calculate vertices based on center, extents, and rotation
        vector2 vertices[4];
        float cosine = cosf(rotation);
        float sine = sinf(rotation);

        vertices[0] = center + vector2(cosine * extents.x - sine * extents.y,
            sine * extents.x + cosine * extents.y);
        vertices[1] = center + vector2(-cosine * extents.x - sine * extents.y,
            -sine * extents.x + cosine * extents.y);
        vertices[2] = center + vector2(-cosine * extents.x + sine * extents.y,
            -sine * extents.x - cosine * extents.y);
        vertices[3] = center + vector2(cosine * extents.x + sine * extents.y,
            sine * extents.x - cosine * extents.y);

        // Draw the OBB
        glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); // Set color to red
        for (int i = 0; i < 4; ++i) {
            glVertex2f(vertices[i].x, vertices[i].y);
        }
        glEnd();

        glPopMatrix(); // Restore the previous matrix state
	}
}