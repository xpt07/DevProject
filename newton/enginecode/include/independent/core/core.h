#pragma once
#include <cmath>
#include <iostream>
#include "precision.h"

namespace Newton
{
    /**
     * @brief A 3D vector class.
     */
    class vector2
    {
    public:
        /**
         * @brief Default constructor, initializes the vector to (0, 0, 0).
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
         */
        vector2 invert() const
        {
            return vector2(-x, -y);
        }

        void clear()
        {
            this->x = 0.0f;
            this->y = 0.0f;
        }

        float magnitude() const
        {
            return std::sqrt(x * x + y * y);
        }

        float squareMagnitude() const
        {
            return x * x + y * y;
        }

        vector2 normalise() const {
            float m = magnitude();
            if (m > 0) return vector2(x / m, y / m);
            return vector2(); // Return zero vector if magnitude is zero
        }

        void operator/=(const float value) {
            if (value != 0) { // Ensure you don't divide by zero
                x /= value;
                y /= value;
            }
            else {
                std::cerr << "Attempt to divide by zero." << std::endl;
            }
        }

        vector2 operator/(const vector2& v) const {
            if (v.x == 0 || v.y == 0) {
                std::cerr << "Attempt to divide by zero vector component." << std::endl;
                return *this; // Return the original vector if divide by zero
            }
            return vector2(x / v.x, y / v.y);
        }


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

        void operator*=(const float value)
        {
            x *= value;
            y *= value;
        }

        vector2 operator*(const float value) const
        {
            return vector2(x * value, y * value);
        }

        void operator+=(const vector2& v)
        {
            x += v.x;
            y += v.y;
        }

        vector2 operator+(const vector2& v) const
        {
            return vector2(x + v.x, y + v.y);
        }

        void operator-=(const vector2& v)
        {
            x -= v.x;
            y -= v.y;
        }

        vector2 operator-(const vector2& v) const
        {
            return vector2(x - v.x, y - v.y);
        }

        float operator*(const vector2& vector) const
        {
            return x * vector.x + y * vector.y;
        }

        bool operator==(const vector2& other) const 
        {
            return x == other.x && y == other.y;
        }

        bool operator!=(const vector2& other) const 
        {
            return x != other.x || y != other.y;
        }

        vector2 rotate(float angle) const {
            float cosTheta = std::cos(angle);
            float sinTheta = std::sin(angle);
            return vector2(cosTheta * x - sinTheta * y, sinTheta * x + cosTheta * y);
        }

        static float dotProduct(const vector2& vector1, const vector2& vector2)
        {
            return vector1.x * vector2.x + vector1.y * vector2.y;
        }

        static float crossProduct(const vector2& vector1, const vector2& vector2)
        {
            return vector1.x * vector2.y - vector1.y * vector2.x;
        }
        
        float x, y; //!< Holds the value along the x and y axis.
    };
}