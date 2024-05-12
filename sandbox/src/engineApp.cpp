/** \file engineApp.cpp
*/
#include "engineApp.h"

engineApp::engineApp()
{
}

engineApp::~engineApp()
{

}

Newton::Application* Newton::startApplication()
{
	return new engineApp();
}