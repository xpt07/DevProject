#include <iostream>
#include <gtest/gtest.h>
#include "core/core.h"
#include "newton/Shape/Circle.h"
#include "newton/RigidBody.h"
#include "core/precision.h"
#include "newton/CollisionUtility.h"
#include "newton/Shape/OBB.h"

// Vector2 Class Tests

TEST(Vector2Test, DefaultConstructor) {
    Newton::vector2 v;
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
}

TEST(Vector2Test, ParameterizedConstructor) {
    Newton::vector2 v(1.0f, 2.0f);
    EXPECT_EQ(v.x, 1.0f);
    EXPECT_EQ(v.y, 2.0f);
}

TEST(Vector2Test, Invert) {
    Newton::vector2 v(-1.0f, 2.0f);
    auto inv = v.invert();
    EXPECT_EQ(inv.x, 1.0f);
    EXPECT_EQ(inv.y, -2.0f);
}

TEST(Vector2Test, Clear) {
    Newton::vector2 v(1.0f, 2.0f);
    v.clear();
    EXPECT_EQ(v.x, 0.0f);
    EXPECT_EQ(v.y, 0.0f);
}

TEST(Vector2Test, Magnitude) {
    Newton::vector2 v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.magnitude(), 5.0f);
}

TEST(Vector2Test, SquareMagnitude) {
    Newton::vector2 v(3.0f, 4.0f);
    EXPECT_FLOAT_EQ(v.squareMagnitude(), 25.0f);
}

TEST(Vector2Test, Normalize) {
    Newton::vector2 v(3.0f, 4.0f);
    auto norm = v.normalise();
    EXPECT_FLOAT_EQ(norm.x, 0.6f);
    EXPECT_FLOAT_EQ(norm.y, 0.8f);
    EXPECT_FLOAT_EQ(norm.magnitude(), 1.0f);
}

TEST(Vector2Test, ScalarMultiplication) {
    Newton::vector2 v(2.0f, 3.0f);
    v *= 1.5f;
    EXPECT_EQ(v.x, 3.0f);
    EXPECT_EQ(v.y, 4.5f);

    Newton::vector2 result = v * 2.0f;
    EXPECT_EQ(result.x, 6.0f);
    EXPECT_EQ(result.y, 9.0f);
}

TEST(Vector2Test, VectorAddition) {
    Newton::vector2 v1(1.0f, 2.0f);
    Newton::vector2 v2(3.0f, 4.0f);

    v1 += v2;
    EXPECT_EQ(v1.x, 4.0f);
    EXPECT_EQ(v1.y, 6.0f);

    Newton::vector2 result = v1 + v2;
    EXPECT_EQ(result.x, 7.0f);
    EXPECT_EQ(result.y, 10.0f);
}

TEST(Vector2Test, VectorSubtraction) {
    Newton::vector2 v1(4.0f, 6.0f);
    Newton::vector2 v2(3.0f, 4.0f);

    v1 -= v2;
    EXPECT_EQ(v1.x, 1.0f);
    EXPECT_EQ(v1.y, 2.0f);

    Newton::vector2 result = v1 - v2;
    EXPECT_EQ(result.x, -2.0f);
    EXPECT_EQ(result.y, -2.0f);
}

TEST(Vector2Test, DotProduct) {
    Newton::vector2 v1(1.0f, 2.0f);
    Newton::vector2 v2(3.0f, 4.0f);

    float dotProductResult = v1 * v2;
    EXPECT_EQ(dotProductResult, 11.0f);
}

TEST(Vector2Test, CrossProduct) {
    Newton::vector2 v1(1.0f, 2.0f);
    Newton::vector2 v2(3.0f, 4.0f);

    float crossProductResult = Newton::vector2::crossProduct(v1, v2);
    EXPECT_EQ(crossProductResult, -2.0f);
}

TEST(Vector2Test, Rotation) {
    Newton::vector2 v(1.0f, 0.0f);
    auto rotatedV = v.rotate(3.14159265f / 2); // 90 degrees in radians
    EXPECT_NEAR(rotatedV.x, 0.0f, 1e-6);
    EXPECT_NEAR(rotatedV.y, 1.0f, 1e-6);
}

// RigidBody Class Tests

TEST(RigidBodyTest, Initialization) {
    Newton::vector2 position(100.0f, 100.0f);
    Newton::Circle circle(50.0, position);
    Newton::RigidBody body(circle, position, 0.0f, Newton::RigidBodyType::Static);
    EXPECT_EQ(body.getPosition().x, 100.0f);
    EXPECT_EQ(body.getPosition().y, 100.0f);
    EXPECT_EQ(body.getRotation(), 0.0f);
    EXPECT_TRUE(body.isStatic());
}

TEST(RigidBodyTest, SetMaterialProperties) {
    Newton::vector2 position(100.0f, 100.0f);
    Newton::Circle circle(50.0, position);
    Newton::RigidBody body(circle, position, 0.0f, Newton::RigidBodyType::Dynamic);

    Newton::Material material(2.0f, 0.8f, 0.5f);
    body.setMaterialProperties(material);

    EXPECT_EQ(body.material.mass, 2.0f);
    EXPECT_EQ(body.material.restitution, 0.8f);
    EXPECT_EQ(body.material.friction, 0.5f);
}

TEST(RigidBodyTest, ApplyForce) {
    Newton::vector2 position(100.0f, 100.0f);
    Newton::Circle circle(50.0, position);
    Newton::RigidBody body(circle, position, 0.0f, Newton::RigidBodyType::Dynamic);

    Newton::vector2 force(10.0f, 5.0f);
    body.applyForce(force);

    float deltaTime = 0.016f; // Assuming 60 FPS
    body.update(deltaTime);

    EXPECT_NE(body.getVelocity().x, 0.0f);
    EXPECT_NE(body.getVelocity().y, 0.0f);
}

// Circle Class Tests

TEST(CircleTest, Initialization) {
    Newton::vector2 position(100.0f, 100.0f);
    Newton::Circle circle(50.0, position);

    EXPECT_EQ(circle.getRadius(), 50.0);
    EXPECT_EQ(circle.getPosition().x, 100.0f);
    EXPECT_EQ(circle.getPosition().y, 100.0f);
}

TEST(CircleTest, SetMaterialProperties) {
    Newton::vector2 position(100.0f, 100.0f);
    Newton::Circle circle(50.0, position, Newton::RigidBodyType::Dynamic);
    Newton::Material material(2.0f, 0.8f, 0.5f);
    circle.setMaterialProperties(material);

    EXPECT_EQ(circle.getRigidBody().material.mass, 2.0f);
    EXPECT_EQ(circle.getRigidBody().material.restitution, 0.8f);
    EXPECT_EQ(circle.getRigidBody().material.friction, 0.5f);
}

TEST(CircleTest, Update) {
    Newton::vector2 position(100.0f, 100.0f);
    Newton::Circle circle(50.0, position, Newton::RigidBodyType::Dynamic);

    Newton::vector2 force(10.0f, 5.0f);
    circle.getRigidBody().applyForce(force);

    float deltaTime = 0.016f; // Assuming 60 FPS
    circle.update(deltaTime);

    EXPECT_NE(circle.getPosition().x, 100.0f);
    EXPECT_NE(circle.getPosition().y, 100.0f);
}

// OBB Class Tests

TEST(OBBTest, Initialization) {
    Newton::vector2 center(100.0f, 100.0f);
    Newton::vector2 extents(50.0f, 30.0f);
    Newton::OBB obb(center, extents);

    EXPECT_EQ(obb.getCenter().x, 100.0f);
    EXPECT_EQ(obb.getCenter().y, 100.0f);
    EXPECT_EQ(obb.getExtents().x, 50.0f);
    EXPECT_EQ(obb.getExtents().y, 30.0f);
}

TEST(OBBTest, SetMaterialProperties) {
    Newton::vector2 center(100.0f, 100.0f);
    Newton::vector2 extents(50.0f, 30.0f);
    Newton::OBB obb(center, extents, Newton::RigidBodyType::Dynamic);

    Newton::Material material(2.0f, 0.8f, 0.5f);
    obb.setMaterialProperties(material);

    EXPECT_EQ(obb.getRigidBody().material.mass, 2.0f);
    EXPECT_EQ(obb.getRigidBody().material.restitution, 0.8f);
    EXPECT_EQ(obb.getRigidBody().material.friction, 0.5f);
}

TEST(OBBTest, Update) {
    Newton::vector2 center(100.0f, 100.0f);
    Newton::vector2 extents(50.0f, 30.0f);
    Newton::OBB obb(center, extents, Newton::RigidBodyType::Dynamic);

    Newton::vector2 force(10.0f, 5.0f);
    obb.getRigidBody().applyForce(force);

    float deltaTime = 0.016f; // Assuming 60 FPS
    obb.update(deltaTime);

    EXPECT_NE(obb.getCenter().x, 100.0f);
    EXPECT_NE(obb.getCenter().y, 100.0f);
}

// CollisionUtility Class Tests

TEST(CircleCollisionTest, NoOverlap) {
    Newton::Circle circle1(1.0, Newton::vector2(0.0f, 0.0f));
    Newton::Circle circle2(1.0, Newton::vector2(3.0f, 0.0f));  // No overlap expected

    bool result = Newton::CollisionUtility::checkCollision(circle1, circle2);
    EXPECT_FALSE(result) << "Circles should not collide.";
}

TEST(CircleCollisionTest, Overlap) {
    Newton::Circle circle1(1.0, Newton::vector2(0.0f, 0.0f));
    Newton::Circle circle2(1.0, Newton::vector2(1.5f, 0.0f));  // Overlap expected

    bool result = Newton::CollisionUtility::checkCollision(circle1, circle2);
    EXPECT_TRUE(result) << "Circles should collide.";
}

TEST(CircleToOBBCollisionTest, NoOverlap) {
    Newton::Circle circle(1.0, Newton::vector2(0.0f, 0.0f));
    Newton::vector2 obbCenter(5.0f, 5.0f);
    Newton::vector2 obbExtents(2.0f, 2.0f);
    Newton::OBB obb(obbCenter, obbExtents);  // No overlap expected

    bool result = Newton::CollisionUtility::checkCollision(circle, obb);
    EXPECT_FALSE(result) << "Circle and OBB should not collide.";
}

TEST(CircleToOBBCollisionTest, Overlap) {
    Newton::Circle circle(1.0, Newton::vector2(0.0f, 0.0f));
    Newton::vector2 obbCenter(0.5f, 0.5f);
    Newton::vector2 obbExtents(1.0f, 1.0f);
    Newton::OBB obb(obbCenter, obbExtents);  // Overlap expected

    bool result = Newton::CollisionUtility::checkCollision(circle, obb);
    EXPECT_TRUE(result) << "Circle and OBB should collide.";
}

TEST(OBBToOBBCollisionTest, NoOverlap) {
    Newton::vector2 center1(0.0f, 0.0f);
    Newton::vector2 extents1(1.0f, 1.0f);
    Newton::OBB obb1(center1, extents1);

    Newton::vector2 center2(5.0f, 5.0f);
    Newton::vector2 extents2(1.0f, 1.0f);
    Newton::OBB obb2(center2, extents2);  // No overlap expected

    bool result = Newton::CollisionUtility::checkCollision(obb1, obb2);
    EXPECT_FALSE(result) << "OBBs should not collide.";
}

TEST(OBBToOBBCollisionTest, Overlap) {
    Newton::vector2 center1(0.0f, 0.0f);
    Newton::vector2 extents1(1.0f, 1.0f);
    Newton::OBB obb1(center1, extents1);

    Newton::vector2 center2(0.5f, 0.5f);
    Newton::vector2 extents2(1.0f, 1.0f);
    Newton::OBB obb2(center2, extents2);  // Overlap expected

    bool result = Newton::CollisionUtility::checkCollision(obb1, obb2);
    EXPECT_TRUE(result) << "OBBs should collide.";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
