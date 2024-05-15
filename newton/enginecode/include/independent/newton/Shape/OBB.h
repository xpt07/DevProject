/** \file OBB.h */
#pragma once

#include "Shape.h"
#include "core/precision.h"
#include "newton/RigidBody.h"
#include <iostream>

namespace Newton
{
    /**
     * @brief Class representing an Oriented Bounding Box (OBB).
     */
    class OBB : public Shape
    {
    public:
        /**
         * @brief Constructor.
         * @param center The center of the OBB.
         * @param extents The extents (half-widths) of the OBB.
         * @param bodyType The type of rigid body associated with the OBB.
         * @param initialRotation The initial rotation of the OBB (in degrees).
         */
        OBB(const vector2& center, const vector2& extents, RigidBodyType bodyType = RigidBodyType::Static, float initialRotation = 0.0f)
            : center(center), extents(extents), rotation(initialRotation), rigidBody(*this, center, initialRotation, bodyType)
        {}

        /**
         * @brief Sets the material properties of the OBB.
         * @param material The material properties to set.
         */
        void setMaterialProperties(const Material& material) {
            rigidBody.setMaterialProperties(material);
        }

        /**
         * @brief Gets the mass of the OBB.
         * @return The mass of the OBB.
         */
        float getMass()
        {
            return rigidBody.material.mass;
        }

        /**
         * @brief Sets the rotation of the OBB.
         * @param angle The rotation angle (in degrees).
         */
        void setRotation(float angle) {
            rotation = angle;
            rigidBody.setRotation(angle);
        }

        /**
         * @brief Gets the rotation of the OBB.
         * @return The rotation angle (in degrees).
         */
        inline const float getRotation() const { return rotation; }

        /**
         * @brief Gets the center of the OBB.
         * @return The center of the OBB.
         */
        inline const vector2& getCenter() const { return center; }

        /**
         * @brief Gets the extents (half-widths) of the OBB.
         * @return The extents of the OBB.
         */
        inline const vector2& getExtents() const { return extents; }

        /**
         * @brief Gets the rigid body associated with the OBB.
         * @return Reference to the rigid body.
         */
        RigidBody& getRigidBody() { return rigidBody; }

        /**
         * @brief Gets the rigid body associated with the OBB (const version).
         * @return Reference to the rigid body.
         */
        const RigidBody& getRigidBody() const { return rigidBody; }

        /**
         * @brief Updates the OBB's properties.
         * @param deltaTime The time step for the update.
         */
        void update(float deltaTime)
        {
            rigidBody.update(deltaTime);
            center = rigidBody.getPosition();
            rotation = rigidBody.getRotation();
        }

        /**
         * @brief Draws the OBB.
         */
        void draw() const override;

        RigidBody rigidBody; //!< Rigid body associated with the OBB.

    private:
        vector2 center;   //!< Center of the OBB.
        vector2 extents; //!< Extents (half-widths) of the OBB.
        float rotation;  //!< Rotation in degrees.
    };
}
