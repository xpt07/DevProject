// Circle.h
#pragma once

#include "Shape.h"
#include "core/precision.h"
#include "newton/RigidBody.h"
#include <iostream>

namespace Newton
{
    class Circle : public Shape
    {
    public:
        Circle(double radius, const vector2& position, const vector2& velocity, float rotation = 0.0f, float angularvelocity = 0.0)
            : radius(radius), position(position), rigidBody(*this, position, velocity, rotation, angularvelocity)
        {}
        Circle(double radius, const vector2& position, float rotation = 0.0)
            : radius(radius), position(position), rigidBody(*this, position, rotation)
        {}

        void setMaterialProperties(const Material& material) {
            rigidBody.setMaterialProperties(material);
        }

        float getMass()
        {
            return rigidBody.material.mass;
        }

        inline double getRadius() const { return radius; }
        inline const vector2& getPosition() const { return position; }
        inline float getArea() const { return PI * powf(static_cast<float>(radius), 2); }
        RigidBody getRigidBody() { return rigidBody; }

        void update(real deltaTime)
        {
            rigidBody.update(deltaTime);
            position = rigidBody.getPosition();
            rotation = rigidBody.getRotation();
        }

        void draw() const override;

        RigidBody rigidBody; //!< Rigid body associated with the circle.

    private:
        double radius;  //!< Radius of the circle.
        vector2 position; //!< Position of the circle.
        float rotation;  // Rotation in degrees
        
    };
}
