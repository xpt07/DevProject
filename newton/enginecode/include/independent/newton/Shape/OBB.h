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
        OBB(const vector2& center, const vector2& extents, const vector2& velocity, float rotation = 0.0f, float angularvelocity = 0.0)
            : center(center), extents(extents), rotation(rotation), rigidBody(*this, center, velocity, rotation, angularvelocity)
        {}

        OBB(const vector2& center, const vector2& extents, float rotation  = 0.0)
            : center(center), extents(extents), rotation(rotation), rigidBody(*this, center, rotation)
        {}

        void setMaterialProperties(const Material& material) {
            rigidBody.setMaterialProperties(material);
        }

        float getMass()
        {
            return rigidBody.material.mass;
        }

        inline const float getRotation() const {return rotation;}
        inline const vector2& getCenter() const { return center; }
        inline const vector2& getExtents() const { return extents; }
        void applyForce(const vector2& force) { rigidBody.applyForce(force); }
        RigidBody getRigidBody() { return rigidBody; }

        void update(float deltaTime)
        {
            rigidBody.update(deltaTime);
            center = rigidBody.getPosition();
            rotation = rigidBody.getRotation();
        }

        void draw() const override;

    private:
        vector2 center;   // Center of the OBB
        vector2 extents; // Extents (half-widths) of the OBB
        float rotation;  // Rotation in degrees
        RigidBody rigidBody; // Rigid body associated with the OBB
    };
}
