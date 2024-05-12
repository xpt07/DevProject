/** \file application.cpp */
#include "engine_pch.h"
#include "core/application.h"
#include "newton/Shape/Circle.h"
#include "newton/Shape/OBB.h"
#include "core/OpenGLWindow.h"

namespace Newton {

	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		if (s_instance == nullptr)
		{
			s_instance = this;
		}
		m_circle = std::make_shared<Newton::Circle>(50.0, Newton::vector2(100.0, 100.0), Newton::vector2(0.0, 0.0));

	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		double lastFrameTime = glfwGetTime();

		while (m_running)
		{
			double currentFrameTime = glfwGetTime();
			deltaTime = static_cast<float>(currentFrameTime - lastFrameTime);
			lastFrameTime = currentFrameTime;

			renderScene();
		};
	}

	void Application::renderScene()
	{
		// Get the OpenGLWindow instance from the singleton pattern
		OpenGLWindow& window = OpenGLWindow::getInstance(800, 600, "Newton Game Engine");

		m_circle->applyForce({1.0, 2.0});

		m_circle->update(deltaTime);

		// Render the circle directly (no need for a separate Renderer class)
		m_circle->draw();

		// Swap buffers and poll events in the window
		window.swapBuffers();
		window.pollEvents();

	}
}