#pragma once

#include "newton/Shape/Shape.h"
#include "core/core.h"
#include <iostream>

namespace Newton
{
    struct Material {
        float mass = 1.0f;           // Default mass
        float restitution = 1.0f;    // Perfectly elastic
        float friction = 0.5f;       // Some default friction

        Material() = default;
        Material(float mass, float restitution, float friction)
            : mass(mass), restitution(restitution), friction(friction) {}
    };

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
        RigidBody(const Shape& shape, const vector2& initialPosition, float initialRotation)
            : shape(shape), type(RigidBodyType::Static), position(initialPosition),
            rotation(initialRotation), velocity(vector2()), angularVelocity(0.0f),
            material() {}

        /**
         * @brief Constructor for a dynamic rigid body.
         * @param shape The shape of the rigid body.
         * @param initialPosition The initial position of the rigid body.
         * @param initialVelocity The initial velocity of the rigid body.
         */
        RigidBody(const Shape& shape, const vector2& initialPosition, const vector2& initialVelocity,
            float initialRotation, float initialAngularVelocity)
            : shape(shape), type(RigidBodyType::Dynamic), position(initialPosition),
            velocity(initialVelocity), rotation(initialRotation),
            angularVelocity(initialAngularVelocity), material() {}

        void setMaterialProperties(const Material& mat) {
            material = mat;
            if (type == RigidBodyType::Static) {
                material.mass = std::numeric_limits<float>::infinity();  // Static bodies are immovable
                material.restitution = mat.restitution;
                material.friction = mat.friction;
            }
        }

        /**
         * @brief Apply a force to the rigid body.
         * @param force The force to be applied.
         */
        void applyForce(const vector2& force, const vector2& point = vector2())
        {
            if (type == RigidBodyType::Dynamic)
            {
                 acceleration += force / material.mass; // Using mass in dynamics

                if (point != vector2()) // Non-zero point means torque will be applied
                {
                    float torque = (point.x - position.x) * force.y - (point.y - position.y) * force.x;
                    angularAcceleration += torque / material.mass; // Assuming moment of inertia = 1 for simplicity
                }
            }
        }

        void applyImpulse(const vector2& impulse) {
            if (type == RigidBodyType::Dynamic) {
                velocity += impulse / material.mass;
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
                // Apply continuous forces, e.g., gravity
                vector2 gravity(0.0f, -9.8f); // Assuming gravity is downwards
                acceleration += gravity;

                // Update velocity using the current acceleration
                velocity += acceleration * deltaTime;

                // Then update position using the new velocity
                position += velocity * deltaTime;


                // Reset acceleration for the next frame
                acceleration = vector2();

                // Update rotation using angular velocity
                rotation += angularVelocity * deltaTime + 0.5f * angularAcceleration * deltaTime * deltaTime;

                // Update angular velocity for the next time step
                angularVelocity += angularAcceleration * deltaTime;
                angularAcceleration = 0; // Reset angular acceleration for the next frame
            }
        }

        /**
         * @brief Get the type of the rigid body (Static or Dynamic).
         * @return The type of the rigid body.
         */
        RigidBodyType getType() const { return type; }

        /**
         * @brief Get the shape of the rigid body.
         * @return Reference to the shape of the rigid body.
         */
        const Shape& getShape() const { return shape; }

        /**
         * @brief Get the current position of the rigid body.
         * @return The current position of the rigid body.
         */
        vector2 getPosition() const { return position; }

        float getRotation() const { return rotation; }

        /**
         * @brief Get the current velocity of the rigid body.
         * @return The current velocity of the rigid body.
         */
        const vector2& getVelocity() const { return velocity; }

        bool isStatic() const { return type == RigidBodyType::Static; }
        bool isDynamic() const { return type == RigidBodyType::Dynamic; }

        Material material;
    private:
        const Shape& shape;          //!< Reference to the shape of the rigid body.
        RigidBodyType type;          //!< Type of the rigid body (Static or Dynamic).
        vector2 position;            //!< Current position of the rigid body.
        vector2 velocity;            //!< Current velocity of the rigid body.
        vector2 acceleration;        //!< Current acceleration of the rigid body (for dynamic objects).
        float rotation;
        float angularVelocity;
        float angularAcceleration;

    };
}