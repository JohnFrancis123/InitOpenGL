#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"


GameController::GameController() {
	m_shader = { };
	m_camera = { };
	m_camera2 = { };
	m_mesh = { }; //default initialization, where m_mesh is an empty Mesh object
	m_effect = 0;
}

GameController::~GameController() {
}

void GameController::Initialize() {
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background

	glEnable(GL_CULL_FACE);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());

	m_camera2 = Camera2(WindowController::GetInstance().GetResolution()); //new camera class.
}

void GameController::RunGame() {
	
	// Show the C++/CLI tool window
	//OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	//window->Show();

	// Create and compile our GLSL program from the shaders
	m_shader = Shader();
	m_shader.LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	m_mesh = Mesh(); //re-initialize m_mesh to ensure it's a fresh object
	m_mesh.Create(&m_shader); //creating the mesh, which sets up its vertex buffer and data
	
	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

		m_mesh.Render(m_camera.GetProjection() * m_camera.GetView());



		//m_mesh.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); //swaping the back buffer to the front to display the rendered image
		glfwPollEvents(); //polling for events, such as keyboard and mouse input
	} 




	while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && //Check if the ESC key is pressed
		glfwWindowShouldClose(win) == 0); //Check if the window was closed

	m_mesh.Cleanup(); //cleaning up the mesh, which deletes its vertex buffer
	m_shader.Cleanup(); //cleaning up the shader, which deletes its program
}