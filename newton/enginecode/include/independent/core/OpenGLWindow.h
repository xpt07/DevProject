#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

namespace Newton {

    class OpenGLWindow {
    public:
        static OpenGLWindow& getInstance(int width, int height, const char* title) {
            static OpenGLWindow instance(width, height, title);
            return instance;
        }

        ~OpenGLWindow() {
            cleanup();
        }

        void run() {
            while (!glfwWindowShouldClose(mainWindow)) {
                render();
                glfwSwapBuffers(mainWindow);
                glfwPollEvents();
            }
        }

        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        }

        void swapBuffers() {
            glfwSwapBuffers(mainWindow);
        }

        void pollEvents() {
            glfwPollEvents();
        }

        int getWidth()
        {
            return width;
        }

        int getHeight()
        {
            return height;
        }

    private:
        int width;
        int height;
        const char* title;
        GLFWwindow* mainWindow;

        OpenGLWindow(int width, int height, const char* title)
            : width(width), height(height), title(title), mainWindow(nullptr) {
            init();
        }

        void init() {
            // Initialize GLFW
            if (glfwInit() == 0) {
                throw std::runtime_error("Failed to initialize GLFW");
            }

            // Set GLFW options (optional)
            // ...

            // Create a windowed mode window and its OpenGL context
            mainWindow = glfwCreateWindow(width, height, title, nullptr, nullptr);
            if (mainWindow == nullptr) {
                throw std::runtime_error("Failed to create GLFW window");
            }

            // Make the window's context current
            glfwMakeContextCurrent(mainWindow);

            // Load OpenGL functions using Glad
            if (!gladLoadGL()) {
                throw std::runtime_error("Failed to load OpenGL");
            }

            // Set GLFW callback functions (optional)
            // ...

            // Additional OpenGL initialization (optional)
            // ...
        }

        void cleanup() {
            glfwTerminate();
        }

        // Disable copy and assignment
        OpenGLWindow(const OpenGLWindow&) = delete;
        OpenGLWindow& operator=(const OpenGLWindow&) = delete;
    };
}
