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
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);
	srand(time(0));
	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());

	//m_camera2 = Camera2(WindowController::GetInstance().GetResolution()); //new camera class.
}

void GameController::RunGame() {
	
	// Show the C++/CLI tool window
	//OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	//window->Show();
#pragma region SetupShaders
	// Create and compile our GLSL program from the shaders
	m_shaderColor = Shader();
	m_shaderColor.LoadShaders("Color.vertexshader", "Color.fragmentshader");
	m_shaderDiffuse = Shader();
	m_shaderDiffuse.LoadShaders("Diffuse.vertexshader", "Diffuse.fragmentshader");
	m_shaderSkybox = Shader();
	m_shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");
	m_shaderFont = Shader();
	m_shaderFont.LoadShaders("Font.vertexshader", "Font.fragmentshader");
#pragma endregion SetupShaders

#pragma region CreateMeshes
	// Create meshes
	Mesh m = Mesh();
	m.Create(&m_shaderColor, "../Assets/Models/teapot.obj");
	m.SetPosition({ 1.0f, 0.0f, 0.0f });
	m.SetColor({ 1.0f, 1.0f, 1.0f });
	m.SetScale({ 0.01f, 0.01f, 0.01f });
	Mesh::Lights.push_back(m);

	//Mesh teapot = Mesh();
	//teapot.Create(&m_shaderDiffuse, "../Assets/Models/teapot.obj");
	//teapot.SetCameraPosition(m_camera.GetPosition());
	//teapot.SetScale({ 0.02f, 0.02f, 0.02f });
	//teapot.SetPosition({ 0.0f, 0.0f, 0.0f });
	//m_meshBoxes.push_back(teapot);

	Mesh box = Mesh();
	box.Create(&m_shaderDiffuse, "../Assets/Models/Cube.obj");
	box.SetCameraPosition(m_camera.GetPosition());
	box.SetScale({ 0.5f, 0.5f, 0.5f });
	box.SetPosition({ 1.0f, 0.0f, 5.0f });
	m_meshBoxes.push_back(box);

	Skybox skybox = Skybox();
	skybox.Create(&m_shaderSkybox, "../Assets/Models/Skybox.obj",
		{ "../Assets/Textures/Skybox/right.jpg",
		  "../Assets/Textures/Skybox/left.jpg",
		  "../Assets/Textures/Skybox/top.jpg",
		  "../Assets/Textures/Skybox/bottom.jpg",
		  "../Assets/Textures/Skybox/front.jpg",
		  "../Assets/Textures/Skybox/back.jpg" });

	//Mesh plane = Mesh();
	//plane.Create(&m_shaderDiffuse, "../Assets/Models/Plane.obj");
	//plane.SetCameraPosition(m_camera.GetPosition());
	//plane.SetScale({ 0.3f, 0.3f, 0.3f });
	//plane.SetPosition({ 0.0f, 0.0f, -1.0f });
	//m_meshBoxes.push_back(plane);

	//Mesh window = Mesh();
	//window.Create(&m_shaderDiffuse, "../Assets/Models/Window.obj");
	//window.SetCameraPosition(m_camera.GetPosition());
	//window.SetScale({ 0.1f, 0.1f, 0.1f });
	//window.SetPosition({ 0.0f, 0.0f, 0.0f });
	//m_meshBoxes.push_back(window);
#pragma endregion CreateMeshes

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 100);
	//m_meshBox = Mesh();
	//m_meshBox.Create(&m_shaderDiffuse);
	//m_meshBox.SetLightColor({ 0.5f, 0.9f, 0.5f });
	//m_meshBox.SetLightPosition(m_meshLight.GetPosition());
	//m_meshBox.SetCameraPosition(m_camera.GetPosition());
	//
	GLFWwindow* win = WindowController::GetInstance().GetWindow();
#pragma region Render
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen
		m_camera.Rotate();
		glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
		skybox.Render(m_camera.GetProjection() * view);
		for (unsigned int count = 0; count < m_meshBoxes.size(); count++) {
			m_meshBoxes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}
		//f.RenderText("Testing Text", 10, 500, 0.5f, { 1.0f, 1.0f, 0.0f });

		//f.RenderText("Testing Text", 10, 700, 0.5f, { 1.0f, 0.0f, 0.0f });

		//f.RenderText("Testing Text", 800, 700, 0.5f, { 1.0f, 1.0f, 1.0f });


		glfwSwapBuffers(WindowController::GetInstance().GetWindow()); //swaping the back buffer to the front to display the rendered image
		glfwPollEvents(); //polling for events, such as keyboard and mouse input
	} 




	while (glfwGetKey(win, GLFW_KEY_ESCAPE) != GLFW_PRESS && //Check if the ESC key is pressed
		glfwWindowShouldClose(win) == 0); //Check if the window was closed
#pragma endregion Render

#pragma region Cleanup
	for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
		Mesh::Lights[count].Cleanup();
	}

	//m_meshLight.Cleanup(); //cleaning up the mesh, which deletes its vertex buffer
	for (unsigned int count = 0; count < m_meshBoxes.size(); count++) {
		m_meshBoxes[count].Cleanup();
	}
	skybox.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup(); //cleaning up the shader, which deletes its program
	m_shaderSkybox.Cleanup();
}
#pragma endregion Cleanup