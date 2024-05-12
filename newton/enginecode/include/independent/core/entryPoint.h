/** \file entryPoint.h
*/
#pragma once

#include "core/application.h"

extern Newton::Application* Newton::startApplication();

int main(int argc, char** argv)
{
	auto application = Newton::startApplication();
	application->run();
	delete application;

	return 0;
}