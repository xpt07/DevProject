/** \file entryPoint.h
*/
#pragma once

#include "core/application.h"

extern Newton::Application* Newton::startApplication();

int main(int argc, char** argv)
{
	auto application = Newton::startApplication();

	Newton::Scene* scene = new Newton::Scene(); // Create a new scene
	application->setScene(scene); // Set the scene in the application
	application->run();

	delete scene;
	delete application;

	return 0;
}