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
        RigidBody(const Shape& shape, const vector2& initialPosition, float initialRotation, RigidBodyType bodyType)
            : shape(shape), type(bodyType), position(initialPosition),
            rotation(initialRotation), material() 
        {}

        void setMaterialProperties(const Material& mat) {
            if (type == RigidBodyType::Static) {
                material.mass = std::numeric_limits<float>::infinity();
                material.restitution = mat.restitution;
                material.friction = mat.friction;
                invMass = 0;
            }
            else if (type == RigidBodyType::Dynamic) {
                material = mat;
                invMass = 1.0f / material.mass;
            }
        }

        /**
         * @brief Apply a force to the rigid body.
         * @param force The force to be applied.
         */
        void applyForce(const vector2& force, const vector2& point = vector2())
        {
            if (type == RigidBodyType::Dynamic) {
                forceAccumulator += force;
            }
        }

        void applyImpulse(const vector2& impulse, const vector2& contactVector = vector2()) {
            if (type == RigidBodyType::Dynamic) {
                impulseAccumulator += impulse;
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
                // Accumulate forces (e.g., gravity)
                forceAccumulator += gravity * material.mass;

                // Calculate acceleration from force
                vector2 acceleration = forceAccumulator * invMass;

                // Apply velocity change due to acceleration
                velocity += acceleration * deltaTime;

                // Apply accumulated impulses directly to velocity
                velocity += impulseAccumulator * invMass;

                // Update position based on new velocity
                position += velocity * deltaTime;

                // Reset accumulators after each update
                forceAccumulator = vector2();
                impulseAccumulator = vector2();

                // Update rotation
                rotation += angularVelocity * deltaTime;
                angularVelocity += angularAcceleration * deltaTime;
                angularAcceleration = 0; // Reset for next frame

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
        vector2& getPosition() { return position; }
        const vector2& getPosition() const { return position; }

        void setPosition(vector2 pos) { position = pos; }

        float getRotation() const { return rotation; }

        /**
         * @brief Get the current velocity of the rigid body.
         * @return The current velocity of the rigid body.
         */
        const vector2& getVelocity() const { return velocity; }

        float getInvMass() const { return invMass; }

        bool isStatic() const { return type == RigidBodyType::Static; }
        bool isDynamic() const { return type == RigidBodyType::Dynamic; }

        Material material;
        float angularVelocity = 0.0f;
    private:
        const Shape& shape;          //!< Reference to the shape of the rigid body.
        RigidBodyType type;          //!< Type of the rigid body (Static or Dynamic).
        vector2 position;            //!< Current position of the rigid body.
        vector2 velocity;            //!< Current velocity of the rigid body.
        vector2 acceleration;        //!< Current acceleration of the rigid body (for dynamic objects).
        float rotation;
        float angularAcceleration = 0.0f;
        float invMass;
        vector2 forceAccumulator;
        vector2 impulseAccumulator;

        vector2 gravity = vector2(0.0f, -9.8f); // Define gravity as a constant vector
    };


}