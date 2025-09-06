#include "GameController.h"
#include "WindowController.h"

GameController::GameController() {
	m_mesh = { }; //default initialization, where m_mesh is an empty Mesh object
}

GameController::~GameController() {
}

void GameController::Initialize() {
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // Dark blue background
}

void GameController::RunGame() {
	m_mesh = Mesh(); //re-initialize m_mesh to ensure it's a fresh object
	m_mesh.Create(); //creating the mesh, which sets up its vertex buffer and data
	
	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
		m_mesh.Render(); //rendering the mesh
		glfwSwapBuffers(win); //swaping the back buffer to the front to display the rendered image
		glfwPollEvents(); //polling for events, such as keyboard and mouse input
	} while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && //Check if the ESC key is pressed
		glfwWindowShouldClose(win) == 0); //Check if the window was closed

	m_mesh.Cleanup(); //cleaning up the mesh, which deletes its vertex buffer
}