#pragma once
#include <cmath>
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
        vector2(const real x, const real y) : x(x), y(y) {}

        /**
         * @brief Inverts the vector (negates each component).
         */
        void invert()
        {
            x = -x;
            y = -y;
        }

        void clear()
        {
            this->x = 0.0f;
            this->y = 0.0f;
        }

        real magnitude() const
        {
            return std::sqrt(x * x + y * y);
        }

        real squareMagnitude() const
        {
            return x * x + y * y;
        }

        void normalise()
        {
            real l = magnitude();
            if (l > 0)
            {
                (*this) *= ((real)1) / l;
            }
        }

        void operator*=(const real value)
        {
            x *= value;
            y *= value;
        }

        vector2 operator*(const real value) const
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

        real operator*(const vector2& vector) const
        {
            return x * vector.x + y * vector.y;
        }

        real dotProduct(const vector2& vector1, const vector2& vector2)
        {
            return vector1.x * vector2.x + vector1.y * vector2.y;
        }   
        
        real x, y; //!< Holds the value along the x and y axis.
    };
}