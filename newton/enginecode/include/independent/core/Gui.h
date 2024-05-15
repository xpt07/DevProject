#pragma once
#include "core/core.h"
#include "newton/Scene.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace Newton
{
	class Scene;

	struct GuiVals {
		// Variables to hold temporary input values
		bool circleAdded = false;
		float circleRadius = 50.0f;
		float circlePosX = 500.0f;
		float circlePosY = 500.0f;
		bool isStatic = false;
		float obbWidth = 300.0f;
		float obbHeight = 50.0f;
		float obbPosX = 400.0f;
		float obbPosY = 300.0f;
	};

	class Gui {

	public:

		Gui(GLFWwindow* window, Scene& scene);
		~Gui();
		void beginRender();
		void render();
		void drawCustomGui();

	private:
		GLFWwindow* m_window;
		GuiVals guiVals;
		Scene& m_scene;

	};
}