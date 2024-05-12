#include <iostream>
#include <gtest/gtest.h>
#include "independent/core/core.h"
#include "independent/newton/Shape/Circle.h"
#include "independent/core/RigidBody.h"
#include "independent/core/precision.h"

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
    v.invert();
    EXPECT_EQ(v.x, 1.0f);
    EXPECT_EQ(v.y, -2.0f);
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
    v.normalise();
    EXPECT_EQ(v.x, 0.6f);
    EXPECT_EQ(v.y, 0.8f);
    EXPECT_FLOAT_EQ(v.magnitude(), 1.0f);
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

TEST(CircleTest, ConstructorAndGetterTest)
{
    Newton::Circle circle(2.5);

    EXPECT_FLOAT_EQ(circle.getRadius(), 2.5);
}

TEST(CircleTest, AreaGetterTest)
{
    Newton::Circle circle(3.0);

    EXPECT_FLOAT_EQ(circle.getArea(), Newton::PI * powf(3, 2));
}

TEST(RigidBodyTest, StaticRigidBodyTest) {
    Newton::Circle circleShape(2.0); // Radius of 2.0
    Newton::RigidBody staticBody(circleShape, Newton::vector2(1.0f, 1.0f));

    // Check if the type is static
    EXPECT_TRUE(staticBody.isStatic(), true);
    EXPECT_TRUE(staticBody.isDynamic(), false);

    // Check if the shape is correct
    EXPECT_EQ(&staticBody.getShape(), &circleShape);

    Newton::vector2 pos(1.0f, 1.0f);
    Newton::vector2 vel(0.0f, 0.0f);
    // Check initial position and velocity (should be zero for static body)
    EXPECT_EQ(staticBody.getPosition().x, pos.x);
    EXPECT_EQ(staticBody.getPosition().y, pos.y);
    EXPECT_EQ(staticBody.getVelocity().x, vel.x);
    EXPECT_EQ(staticBody.getVelocity().y, vel.y);
}

TEST(RigidBodyTest, DynamicRigidBodyTest) {
    Newton::Circle circleShape(3.0); // Radius of 3.0
    Newton::vector2 initialPosition(1.0, 2.0);
    Newton::vector2 initialVelocity(3.0, 4.0);
    Newton::RigidBody dynamicBody(circleShape, initialPosition, initialVelocity);

    // Check if the type is dynamic
    EXPECT_TRUE(dynamicBody.isDynamic(), true);
    EXPECT_TRUE(dynamicBody.isStatic(), false);

    // Check if the shape is correct
    EXPECT_EQ(&dynamicBody.getShape(), &circleShape);

    // Check initial position and velocity
    EXPECT_EQ(dynamicBody.getPosition().x, initialPosition.x);
    EXPECT_EQ(dynamicBody.getPosition().y, initialPosition.y);
    EXPECT_EQ(dynamicBody.getVelocity().x, initialVelocity.x);
    EXPECT_EQ(dynamicBody.getVelocity().y, initialVelocity.y);
}

// Test force application and update for dynamic rigid body
TEST(RigidBodyTest, DynamicRigidBodyForcesAndUpdatesTest) {
    Newton::Circle circleShape(1.0); // Radius of 1.0
    Newton::RigidBody dynamicBody(circleShape, Newton::vector2(0.0, 0.0), Newton::vector2(0.0, 0.0));

    // Apply force and check acceleration
    Newton::vector2 force(1.0, 0.5); // Gravity force
    dynamicBody.applyForce(force);
    EXPECT_EQ(dynamicBody.getPosition().x, 0.0);
    EXPECT_EQ(dynamicBody.getPosition().y, 0.0);
    EXPECT_EQ(dynamicBody.getVelocity().x, 0.0);
    EXPECT_EQ(dynamicBody.getVelocity().y, 0.0);

    // Update and check new position and velocity after one time step
    dynamicBody.update(1.0);
    EXPECT_EQ(dynamicBody.getPosition().x, 1.0);
    EXPECT_EQ(dynamicBody.getPosition().y, 0.5);
    EXPECT_EQ(dynamicBody.getVelocity().x, 1.0);
    EXPECT_EQ(dynamicBody.getVelocity().y, 0.5);

    // Update again and check further changes
    dynamicBody.update(1.0);
    EXPECT_EQ(dynamicBody.getPosition().x, 2.0);
    EXPECT_EQ(dynamicBody.getPosition().y, 1.0);
    EXPECT_EQ(dynamicBody.getVelocity().x, 1.0);
    EXPECT_EQ(dynamicBody.getVelocity().y, 0.5);
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	std::cout << std::endl << "Press enter to continue" << std::endl;
	std::getchar();
	return 0;
}