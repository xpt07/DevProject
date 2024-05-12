/** \file application.h */
#pragma once

#include "Renderer.h"
#include <memory>
#include <chrono>

namespace Newton {

	class Application
	{
	public:
		virtual ~Application();
		inline static Application& getInstance() { return *s_instance; }
		void run();
		void renderScene(); // New function for rendering shapes
	protected:
		Application();
	private:
		double deltaTime;
		static Application* s_instance;
		bool m_running = true;
		std::shared_ptr<Newton::Circle> m_circle;
	};

	Application* startApplication();
}
