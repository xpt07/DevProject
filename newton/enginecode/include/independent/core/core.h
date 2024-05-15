/** \file core.h */
#pragma once
#include <cmath>
#include <iostream>
#include "precision.h"

namespace Newton
{
    /**
     * @brief A 2D vector class.
     */
    class vector2
    {
    public:
        /**
         * @brief Default constructor, initializes the vector to (0, 0).
         */
        vector2() : x(0), y(0) {}

        /**
         * @brief Parameterized constructor, initializes the vector with specified values.
         * @param x The x-component of the vector.
         * @param y The y-component of the vector.
         */
        vector2(const float x, const float y) : x(x), y(y) {}

        /**
         * @brief Inverts the vector (negates each component).
         * @return The inverted vector.
         */
        vector2 invert() const
        {
            return vector2(-x, -y);
        }

        /**
         * @brief Clears the vector, setting its components to zero.
         */
        void clear()
        {
            this->x = 0.0f;
            this->y = 0.0f;
        }

        /**
         * @brief Calculates the magnitude (length) of the vector.
         * @return The magnitude of the vector.
         */
        float magnitude() const
        {
            return std::sqrt(x * x + y * y);
        }

        /**
         * @brief Calculates the square of the magnitude of the vector.
         * @return The square of the magnitude of the vector.
         */
        float squareMagnitude() const
        {
            return x * x + y * y;
        }

        /**
         * @brief Normalizes the vector.
         * @return The normalized vector.
         */
        vector2 normalise() const {
            float m = magnitude();
            if (m > 0) return vector2(x / m, y / m);
            return vector2(); // Return zero vector if magnitude is zero
        }

        /**
         * @brief Divides the vector by a scalar value.
         * @param value The scalar value to divide by.
         */
        void operator/=(const float value) {
            if (value != 0) {
                x /= value;
                y /= value;
            }
            else {
                std::cerr << "Attempt to divide by zero." << std::endl;
            }
        }

        /**
         * @brief Divides the vector component-wise by another vector.
         * @param v The vector to divide by.
         * @return The resulting vector.
         */
        vector2 operator/(const vector2& v) const {
            if (v.x == 0 || v.y == 0) {
                std::cerr << "Attempt to divide by zero vector component." << std::endl;
                return *this; // Return the original vector if divide by zero
            }
            return vector2(x / v.x, y / v.y);
        }

        /**
         * @brief Divides the vector by a scalar value.
         * @param value The scalar value to divide by.
         * @return The resulting vector.
         */
        vector2 operator/(const float value) const
        {
            if (value != 0) {
                return vector2(x / value, y / value);
            }
            else {
                std::cerr << "Attempt to divide by zero." << std::endl;
                return *this; // Return the original vector if divide by zero
            }
        }

        /**
         * @brief Multiplies the vector by a scalar value.
         * @param value The scalar value to multiply by.
         */
        void operator*=(const float value)
        {
            x *= value;
            y *= value;
        }

        /**
         * @brief Multiplies the vector by a scalar value.
         * @param value The scalar value to multiply by.
         * @return The resulting vector.
         */
        vector2 operator*(const float value) const
        {
            return vector2(x * value, y * value);
        }

        /**
         * @brief Adds another vector to this vector.
         * @param v The vector to add.
         */
        void operator+=(const vector2& v)
        {
            x += v.x;
            y += v.y;
        }

        /**
         * @brief Adds another vector to this vector.
         * @param v The vector to add.
         * @return The resulting vector.
         */
        vector2 operator+(const vector2& v) const
        {
            return vector2(x + v.x, y + v.y);
        }

        /**
         * @brief Subtracts another vector from this vector.
         * @param v The vector to subtract.
         */
        void operator-=(const vector2& v)
        {
            x -= v.x;
            y -= v.y;
        }

        /**
         * @brief Subtracts another vector from this vector.
         * @param v The vector to subtract.
         * @return The resulting vector.
         */
        vector2 operator-(const vector2& v) const
        {
            return vector2(x - v.x, y - v.y);
        }

        /**
         * @brief Calculates the dot product of this vector with another vector.
         * @param vector The other vector.
         * @return The dot product.
         */
        float operator*(const vector2& vector) const
        {
            return x * vector.x + y * vector.y;
        }

        /**
         * @brief Checks if this vector is equal to another vector.
         * @param other The other vector.
         * @return True if the vectors are equal, false otherwise.
         */
        bool operator==(const vector2& other) const
        {
            return x == other.x && y == other.y;
        }

        /**
         * @brief Checks if this vector is not equal to another vector.
         * @param other The other vector.
         * @return True if the vectors are not equal, false otherwise.
         */
        bool operator!=(const vector2& other) const
        {
            return x != other.x || y != other.y;
        }

        /**
         * @brief Rotates the vector by a specified angle.
         * @param angle The angle of rotation (in radians).
         * @return The rotated vector.
         */
        vector2 rotate(float angle) const {
            float cosTheta = std::cos(angle);
            float sinTheta = std::sin(angle);
            return vector2(cosTheta * x - sinTheta * y, sinTheta * x + cosTheta * y);
        }

        /**
         * @brief Calculates the dot product of two vectors.
         * @param vector1 The first vector.
         * @param vector2 The second vector.
         * @return The dot product of the two vectors.
         */
        static float dotProduct(const vector2& vector1, const vector2& vector2)
        {
            return vector1.x * vector2.x + vector1.y * vector2.y;
        }

        /**
         * @brief Calculates the cross product of two vectors.
         * @param vector1 The first vector.
         * @param vector2 The second vector.
         * @return The cross product of the two vectors.
         */
        static float crossProduct(const vector2& vector1, const vector2& vector2)
        {
            return vector1.x * vector2.y - vector1.y * vector2.x;
        }

        float x, y; //!< Holds the value along the x and y axis.
    };
}
