#include <iostream>
#include <gtest/gtest.h>
#include "core/core.h"
#include "newton/Shape/Circle.h"
#include "newton/RigidBody.h"
#include "core/precision.h"
#include "newton/CollisionUtility.h"

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


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	std::cout << std::endl << "Press enter to continue" << std::endl;
	std::getchar();
	return 0;
}