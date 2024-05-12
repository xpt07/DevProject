// Circle.h
#pragma once
#include "Shape.h"
#include "core/precision.h"
#include "core/RigidBody.h"
#include <iostream>

namespace Newton
{
    class Circle : public Shape
    {
    public:
        Circle(double radius, const vector2& position, const vector2& velocity)
            : radius(radius), position(position), rigidBody(*this, position, velocity)
        {}

        inline double getRadius() const
        {
            return radius;
        }

        inline const vector2& getPosition() const
        {
            return position;
        }

        // Add a method to apply a force to the associated rigid body
        void applyForce(const vector2& force)
        {
            rigidBody.applyForce(force);
        }

        inline real getArea() const
        {
            return PI * powf(static_cast<float>(radius), 2);
        }

        void update(real deltaTime)
        {
            rigidBody.update(deltaTime);
            position = rigidBody.getPosition();
        }

        RigidBody getRigidBody()
        {
            return rigidBody;
        }

        void draw() const override;

    private:
        double radius;  //!< Radius of the circle.
        vector2 position; //!< Position of the circle.
        RigidBody rigidBody; //!< Rigid body associated with the circle.
    };
}
