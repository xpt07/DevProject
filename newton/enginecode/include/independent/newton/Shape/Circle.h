/** \file Circle.h */

#pragma once

#include "Shape.h"
#include "core/precision.h"
#include "newton/RigidBody.h"
#include <iostream>

namespace Newton
{
    /**
     * @class Circle
     * @brief Class representing a circle shape with a rigid body for physics calculations.
     */
    class Circle : public Shape
    {
    public:
        /**
         * @brief Constructs a Circle object.
         * @param radius Radius of the circle.
         * @param position Initial position of the circle.
         * @param bodyType Type of the rigid body (Static or Dynamic).
         * @param rotation Initial rotation of the circle in degrees.
         */
        Circle(double radius, const vector2& position, RigidBodyType bodyType = RigidBodyType::Static, float rotation = 0.0f)
            : radius(radius), position(position), rigidBody(*this, position, rotation, bodyType)
        {}

        /**
         * @brief Sets the material properties for the circle's rigid body.
         * @param material Struct containing material properties like mass, restitution, and friction.
         */
        void setMaterialProperties(const Material& material) {
            rigidBody.setMaterialProperties(material);
        }

        /**
         * @brief Gets the mass of the circle from its material properties.
         * @return Mass of the circle.
         */
        float getMass()
        {
            return rigidBody.material.mass;
        }

        /**
         * @brief Sets the position of the circle.
         * @param pos New position of the circle.
         */
        void setPosition(vector2 pos) { position = pos; }

        /**
         * @brief Retrieves the radius of the circle.
         * @return Radius of the circle.
         */
        inline double getRadius() const { return radius; }

        /**
         * @brief Retrieves the current position of the circle.
         * @return Current position of the circle.
         */
        inline const vector2 getPosition() const { return position; }

        /**
         * @brief Calculates the area of the circle.
         * @return Area of the circle.
         */
        inline float getArea() const { return PI * powf(static_cast<float>(radius), 2); }

        /**
         * @brief Accessor for the circle's rigid body.
         * @return Reference to the circle's rigid body.
         */
        RigidBody& getRigidBody() { return rigidBody; }

        /**
         * @brief Constant accessor for the circle's rigid body.
         * @return Constant reference to the circle's rigid body.
         */
        const RigidBody& getRigidBody() const { return rigidBody; }

        /**
         * @brief Updates the circle's state including its rigid body's dynamics.
         * @param deltaTime Time step for the update.
         */
        void update(float deltaTime)
        {
            rigidBody.update(deltaTime);
            position = rigidBody.getPosition();
            rotation = rigidBody.getRotation();
        }

        /**
         * @brief Draws the circle. Needs to be implemented in derived classes.
         */
        void draw() const override;

        RigidBody rigidBody; //!< Rigid body associated with the circle.

    private:
        double radius;  //!< Radius of the circle.
        vector2 position; //!< Position of the circle.
        float rotation;  //!< Rotation of the circle in degrees.
    };
}
