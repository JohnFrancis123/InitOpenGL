#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"


GameController::GameController() {
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_camera = { };
	m_meshes.clear();
	m_meshLight = { };
	m_shaderFont = { };
	m_shaderPost = { };
}

GameController::~GameController() {
}

void GameController::Initialize() {
	GLFWwindow* window = WindowController::GetInstance().GetWindow(); // Call this first, as it creates a window required by GLEW
	M_ASSERT(glewInit() == GLEW_OK, "Failed to initialize GLEW."); // Initialize GLEW
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); // Ensure we can capture the escape key
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CW);
	srand(time(0));
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a default perspective camera
	m_camera = Camera(WindowController::GetInstance().GetResolution());

	Resolution r = WindowController::GetInstance().GetResolution();
	glViewport(0, 0, r.m_width, r.m_height);
	m_camera = Camera(r);
}

void GameController::RunGame() {

	// Show the C++/CLI tool window
	OpenGL::ToolWindow^ window = gcnew OpenGL::ToolWindow();
	window->Show();
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
	m_shaderPost = Shader();
	m_shaderPost.LoadShaders("PostProcessor.vertexshader", "PostProcessor.fragmentshader");
#pragma endregion SetupShaders

#pragma region CreateMeshes
	// Create meshes
	Mesh m = Mesh();
	m.Create(&m_shaderColor, "../Assets/Models/teapot.obj");
	m.SetPosition({ 0.0f, 0.8f, 1.0f });
	m.SetColor({ 1.0f, 1.0f, 1.0f });
	m.SetScale({ 0.01f, 0.01f, 0.01f });
	Mesh::Lights.push_back(m);

	//for (int i = 0; i < 1000; i++) {
	Mesh box = Mesh();
	box.Create(&m_shaderDiffuse, "../Assets/Models/Cube.obj", 10);
	box.SetCameraPosition(m_camera.GetPosition());
	box.SetScale({ 0.1f, 0.1f, 0.1f });
	box.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes.push_back(box);
	//}

	//Mesh fighter = Mesh();
	//fighter.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	//fighter.SetCameraPosition(m_camera.GetPosition());
	//fighter.SetScale({ 0.002f, 0.002f, 0.002f });
	//fighter.SetPosition({ 0.0f, 0.0f, 0.0f });
	//m_meshes.push_back(fighter);

	//Mesh wall = Mesh();
	//wall.Create(&m_shaderDiffuse, "../Assets/Models/Wall.obj");
	//wall.SetCameraPosition(m_camera.GetPosition());
	//wall.SetScale({ 0.05f, 0.05f, 0.05f });
	//wall.SetPosition({ 0.0f, 1.0f, 1.0f });
	//m_meshes.push_back(wall);

#pragma endregion CreateMeshes

	Fonts f = Fonts();
	f.Create(&m_shaderFont, "arial.ttf", 40);
	m_postProcessor = PostProcessor();
	m_postProcessor.Create(&m_shaderPost);

	GLFWwindow* win = WindowController::GetInstance().GetWindow();
#pragma region Render
	double lastTime = glfwGetTime();
	int fps = 0;
	string fpsS = "0";

	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

		m_postProcessor.Start();
		//m_camera.Rotate();
		glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
		for (unsigned int count = 0; count < m_meshes.size(); count++) {
			m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
			Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
		}

		double currentTime = glfwGetTime();
		fps++;
		if (currentTime - lastTime >= 1.0) {
			fpsS = "FPS: " + to_string(fps);
			fps = 0;
			lastTime = currentTime;
		}
		m_postProcessor.End();

		f.RenderText(fpsS, 100, 300, 0.5f, { 1.0f, 1.0f, 0.0f });
		//f.RenderText("HELLO", 100, 100, 0.5f, {1.0f, 1.0f, 0.0f});

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
	for (unsigned int count = 0; count < m_meshes.size(); count++) {
		m_meshes[count].Cleanup();
	}
	//skybox.Cleanup();
	f.Cleanup();
	m_postProcessor.Cleanup();
	m_shaderDiffuse.Cleanup();
	m_shaderColor.Cleanup(); //cleaning up the shader, which deletes its program
	m_shaderSkybox.Cleanup();
	m_shaderFont.Cleanup();
}
#pragma endregion Cleanup