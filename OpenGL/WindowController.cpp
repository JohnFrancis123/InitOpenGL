#include "WindowController.h"

WindowController::WindowController(){
	m_window = nullptr;
}
//
WindowController::~WindowController() {
	if (m_window != nullptr) {
		glfwTerminate(); // Terminate GLFW, clearing any resources allocated by GLFW.
		m_window = nullptr; // Set the window pointer to nullptr after termination
	}
}

void WindowController::NewWindow() {
	//glfwInit() means to initialize the GLFW library, and it must be called before any other GLFW functions because it sets up the necessary resources and state for the library to function correctly.
	M_ASSERT(glfwInit(), "Failed to initialize GLFW."); // Initialize GLFW

	// Open a window and create its OpenGL context
	glfwWindowHint(GLFW_SAMPLES, 4); //if can, use 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //if we can, initialize version 3.1 of openGL. Otherwise, use a lower version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	M_ASSERT((m_window = glfwCreateWindow(1024, 768, "A sample scene", NULL, NULL)) != nullptr, "Failed to open GLFW window."); // Open a window and create its OpenGL context
	glfwMakeContextCurrent(m_window); //initialize GLEW to set this as our current window
}

Resolution WindowController::GetResolution() {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	return Resolution(mode->width, mode->height);
}