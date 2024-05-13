/** \file application.h */
#pragma once

#include "newton/Scene.h"
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

		void setScene(Scene* scene) { m_scene = scene; }  // Method to set the current scene
		Scene* getScene() const { return m_scene; }     // Method to get the current scene
	protected:
		Application();
	private:
		double deltaTime;
		static Application* s_instance;
		bool m_running = true;
		Scene* m_scene = nullptr;     // Pointer to the scene
	};

	Application* startApplication();
}
