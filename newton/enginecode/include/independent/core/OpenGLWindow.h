/** \file OpenGLWindow.h */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <stdexcept>

namespace Newton {

    /**
     * @brief A singleton class representing an OpenGL window.
     */
    class OpenGLWindow {
    public:
        /**
         * @brief Gets the instance of the OpenGLWindow singleton.
         * @param width The width of the window.
         * @param height The height of the window.
         * @param title The title of the window.
         * @return Reference to the OpenGLWindow instance.
         */
        static OpenGLWindow& getInstance(int width, int height, const char* title) {
            static OpenGLWindow instance(width, height, title);
            return instance;
        }

        /**
         * @brief Destructor.
         */
        ~OpenGLWindow() {
            cleanup();
        }

        /**
         * @brief Runs the OpenGL main loop.
         */
        void run() {
            while (!glfwWindowShouldClose(mainWindow)) {
                render();
                glfwSwapBuffers(mainWindow);
                glfwPollEvents();
            }
        }

        /**
         * @brief Clears the color and depth buffers.
         */
        void render() {
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        }

        /**
         * @brief Swaps the front and back buffers.
         */
        void swapBuffers() {
            glfwSwapBuffers(mainWindow);
        }

        /**
         * @brief Processes events.
         */
        void pollEvents() {
            glfwPollEvents();
        }

        /**
         * @brief Gets the width of the window.
         * @return The width of the window.
         */
        int getWidth() {
            return width;
        }

        /**
         * @brief Gets the height of the window.
         * @return The height of the window.
         */
        int getHeight() {
            return height;
        }

    private:
        int width; //!< The width of the window.
        int height; //!< The height of the window.
        const char* title; //!< The title of the window.
        GLFWwindow* mainWindow; //!< Pointer to the GLFW window.

        /**
         * @brief Constructor.
         * @param width The width of the window.
         * @param height The height of the window.
         * @param title The title of the window.
         */
        OpenGLWindow(int width, int height, const char* title)
            : width(width), height(height), title(title), mainWindow(nullptr) {
            init();
        }

        /**
         * @brief Initializes GLFW and OpenGL.
         */
        void init() {
            // Initialize GLFW
            if (glfwInit() == 0) {
                throw std::runtime_error("Failed to initialize GLFW");
            }

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
        }

        /**
         * @brief Cleans up GLFW.
         */
        void cleanup() {
            glfwTerminate();
        }

        // Disable copy and assignment
        OpenGLWindow(const OpenGLWindow&) = delete;
        OpenGLWindow& operator=(const OpenGLWindow&) = delete;
    };
}

