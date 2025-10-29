#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"


GameController::GameController() {
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_camera = { };
	m_meshBoxes.clear();
	m_meshLight = { };
}

GameController::~GameController() {
}

void GameController::Initialize() {
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f); // Grey background

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	srand(time(0));
	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());

	//m_camera2 = Camera2(WindowController::GetInstance().GetResolution()); //new camera class.
}

void GameController::RunGame() {
	
	// Show the C++/CLI tool window
	//OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	//window->Show();

	// Create and compile our GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.Fragmentshader");

	// Create meshes
	for (int count = 0; count < 4; count++) 
	{
		Mesh m = Mesh();
		//m_meshLight = Mesh(); //re-initialize m_mesh to ensure it's a fresh object
		m.Create(&m_shaderColor); //creating the mesh, which sets up its vertex buffer and data
		m.SetPosition({ 0.5f + (float)count / 10.0f, 0.0f, -0.5f});
		m.SetColor({ glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f), glm::linearRand(0.0f, 1.0f) });
		m.SetScale({ 0.1f, 0.1f, 0.1f });
		Mesh::Lights.push_back(m);
	}

	for (int col = 0; col < 10; col++) {
		for (int count = 0; count < 10; count++) {
			Mesh box = Mesh();
			box.Create(&m_shaderDiffuse);
			//box.SetLightColor({ 1.0f, 1.0f, 1.0f });
			//box.SetLightPosition(m_meshLight.GetPosition());
			box.SetCameraPosition(m_camera.GetPosition());
			box.SetScale({ 0.1f, 0.1f, 0.1f });
			box.SetPosition({ 0.0f, -0.5f + (float)count / 10.0f, -0.2f + (float)col / 10.0f });
			m_meshBoxes.push_back(box);
		}
	}

	//m_meshBox = Mesh();
	//m_meshBox.Create(&m_shaderDiffuse);
	//m_meshBox.SetLightColor({ 0.5f, 0.9f, 0.5f });
	//m_meshBox.SetLightPosition(m_meshLight.GetPosition());
	//m_meshBox.SetCameraPosition(m_camera.GetPosition());

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		//m_meshBox.Render(m_camera.GetProjection() * m_camera.GetView());
		for (unsigned int count = 0; count < m_meshBoxes.size(); count++) {
			m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		//m_meshLight.Render(m_camera.GetProjection() * m_camera.GetView());


		//m_mesh.Render(m_camera.GetProjection() * m_camera.GetView());
		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); //swaping the back buffer to the front to display the rendered image
		glfwPollEvents(); //polling for events, such as keyboard and mouse input
	} 




	while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && //Check if the ESC key is pressed
		glfwWindowShouldClose(win) == 0); //Check if the window was closed

	for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
		Mesh::Lights[count].Cleanup();
	}

	//m_meshLight.Cleanup(); //cleaning up the mesh, which deletes its vertex buffer
	for (unsigned int count = 0; count < m_meshBoxes.size(); count++) {
		m_meshBoxes[count].Cleanup();
	}
	//m_meshBox.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup(); //cleaning up the shader, which deletes its program
}