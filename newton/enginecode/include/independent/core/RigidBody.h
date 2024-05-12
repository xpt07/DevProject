#pragma once

#include "newton/Shape/Shape.h"
#include "core.h"
#include <iostream>

namespace Newton
{
    /**
     * @brief Enumeration for rigid body types.
     */
    enum class RigidBodyType
    {
        Static,
        Dynamic
    };

    /**
     * @brief Class representing a 2D rigid body.
     */
    class RigidBody
    {
    public:
        /**
         * @brief Constructor for a static rigid body.
         * @param shape The shape of the rigid body.
         */
        RigidBody(const Shape& shape, const vector2& initialPosition)
            : shape(shape), type(RigidBodyType::Static), position(initialPosition), velocity(vector2())
        {}

        /**
         * @brief Constructor for a dynamic rigid body.
         * @param shape The shape of the rigid body.
         * @param initialPosition The initial position of the rigid body.
         * @param initialVelocity The initial velocity of the rigid body.
         */
        RigidBody(const Shape& shape, const vector2& initialPosition, const vector2& initialVelocity)
            : shape(shape), type(RigidBodyType::Dynamic), position(initialPosition), velocity(initialVelocity) {}

        /**
         * @brief Apply a force to the rigid body.
         * @param force The force to be applied.
         */
        void applyForce(const vector2& force)
        {
            if (type == RigidBodyType::Dynamic)
            {
                // For simplicity, assuming unit mass
                acceleration += force;
            }
        }

        /**
         * @brief Update the rigid body's position and velocity based on time.
         * @param deltaTime The time step for the update.
         */
        void update(real deltaTime)
        {
            if (type == RigidBodyType::Dynamic)
            {
                // Print debugging information before the update
                std::cout << "Before update - Position: " << position.x << ", " << position.y << " Velocity: " << velocity.x << ", " << velocity.y << std::endl;

                // Update velocity and position using basic physics equations
                velocity += acceleration * deltaTime;
                position += velocity * deltaTime;

                // Reset acceleration for the next frame
                acceleration = vector2();

                // Print debugging information after the update
                std::cout << "After update - Position: " << position.x << ", " << position.y << " Velocity: " << velocity.x << ", " << velocity.y << std::endl;
            }
        }




        /**
         * @brief Get the type of the rigid body (Static or Dynamic).
         * @return The type of the rigid body.
         */
        RigidBodyType getType() const
        {
            return type;
        }

        /**
         * @brief Get the shape of the rigid body.
         * @return Reference to the shape of the rigid body.
         */
        const Shape& getShape() const
        {
            return shape;
        }

        /**
         * @brief Get the current position of the rigid body.
         * @return The current position of the rigid body.
         */
        const vector2& getPosition() const
        {
            return position;
        }

        /**
         * @brief Get the current velocity of the rigid body.
         * @return The current velocity of the rigid body.
         */
        const vector2& getVelocity() const
        {
            return velocity;
        }

        bool isStatic() const
        {
            return type == RigidBodyType::Static;
        }

        bool isDynamic() const
        {
            return type == RigidBodyType::Dynamic;
        }
    private:
        const Shape& shape;          //!< Reference to the shape of the rigid body.
        RigidBodyType type;          //!< Type of the rigid body (Static or Dynamic).
        vector2 position;            //!< Current position of the rigid body.
        vector2 velocity;            //!< Current velocity of the rigid body.
        vector2 acceleration;        //!< Current acceleration of the rigid body (for dynamic objects).
    };
}