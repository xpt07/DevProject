/** \file Shape.h */
#pragma once

#include <cmath>
#include "core/core.h"

namespace Newton
{
    /**
     * @brief Base class for 2D shapes.
     */
    class Shape
    {
    public:
        /**
         * @brief Destructor.
         */
        virtual ~Shape() = default;

        /**
         * @brief Draw the shape.
         */
        virtual void draw() const = 0;

    };
}
