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

			if (m_scene) {
				m_scene->onUpdate(deltaTime);
			}

			renderScene();
		};
	}

	void Application::renderScene()
	{
		// Get the OpenGLWindow instance from the singleton pattern
		OpenGLWindow& window = OpenGLWindow::getInstance(800, 600, "Newton Game Engine");

		// Set up the rendering state for a simple example
		glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		if (m_scene) {
			m_scene->onDraw();  // Delegate the rendering to the scene
		}

		// Swap buffers and poll events in the window
		window.swapBuffers();
		window.pollEvents();

	}

}