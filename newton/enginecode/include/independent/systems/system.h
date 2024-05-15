/** \file system.h */

#pragma once

#include <cstdarg>

/**
 * @class System
 * @brief Interface class for all systems
 */
namespace Newton {

    enum class SystemSignal { None = 0 };

    class System
    {
    public:
        /**
         * @brief Destructor.
         */
        virtual ~System() {};

        /**
         * @brief Start the system.
         * @param init Initialization signal (optional).
         * @param ... Additional parameters (optional).
         */
        virtual void start(SystemSignal init = SystemSignal::None, ...) = 0;

        /**
         * @brief Stop the system.
         * @param close Closing signal (optional).
         * @param ... Additional parameters (optional).
         */
        virtual void stop(SystemSignal close = SystemSignal::None, ...) = 0;
    };
}

