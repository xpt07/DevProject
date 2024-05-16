/** \file entryPoint.h */
#include "core/application.h"

/**
 * @brief Entry point of the program.
 * @return Exit code.
 */
int main(int argc, char** argv)
{
    auto application = Newton::startApplication();

    // Create a new scene and transfer ownership to the Application via std::unique_ptr
    std::unique_ptr<Newton::Scene> scene = std::make_unique<Newton::Scene>();
    application->setScene(std::move(scene)); // Set the scene in the application

    application->run();

    // No need to delete scene or application; handled by smart pointers and the application's destructor
    return 0;
}
