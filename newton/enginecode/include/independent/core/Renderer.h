#pragma once
#include "newton/Shape/Circle.h"
#include "newton/Shape/OBB.h"
#include "RigidBody.h"

namespace Newton
{
    class Renderer
    {
    public:
        Renderer(int windowWidth, int windowHeight);
        ~Renderer();

        void renderCircle(const Circle& circle);

    private:
        int windowWidth;
        int windowHeight;
    };
}

