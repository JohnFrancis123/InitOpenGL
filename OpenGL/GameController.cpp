#include "GameController.h"
#include "WindowController.h"
#include "ToolWindow.h"


GameController::GameController() {
	m_shaderColor = { };
	m_shaderDiffuse = { };
	m_camera = { };
	m_meshes.clear();
	m_shaderFont = { };
	m_shaderPost = { };

	m_specularColor = { 1.0f, 1.0f, 1.0f };

	m_translateEnabled = false;
	m_wireframeEnabled = false;
	m_rotateEnabled = false;
	m_scaleEnabled = false;
	
	m_mesh = nullptr; //while this is not manually freed, it just points to a value on the stack so we don't really need to manually delete it.

	m_modelName = "";
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

// Helper to capture cursor vector relative to center (updates m_mouseClickDirection)
void GameController::CaptureMouseClickDirection() {
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	if (!window) return;
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Get window size and compute center
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	double centerX = width / 2.0;
	double centerY = height / 2.0;

	m_mouseClickDirection.x = static_cast<float>(xpos - centerX);
	m_mouseClickDirection.y = static_cast<float>(centerY - ypos);
}

// Consolidated helper to update button state and capture direction
void GameController::UpdateBtnState(int _glfwButton, bool& _stateFlag) {
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	if (!window) return;

	if (glfwGetMouseButton(window, _glfwButton) == GLFW_PRESS) {
		_stateFlag = true;
		CaptureMouseClickDirection();
	} else {
		_stateFlag = false;
	}
}

// Update state when left mouse is pressed
void GameController::UpdateOnLeftMouse() {
	UpdateBtnState(GLFW_MOUSE_BUTTON_LEFT, m_leftMouseClicked);
}

// Update state when middle mouse is pressed
void GameController::UpdateOnMiddleMouse() {
	UpdateBtnState(GLFW_MOUSE_BUTTON_MIDDLE, m_middleMouseClicked);
}

// Returns the last mouse-click direction vector relative to the center of the window (not normalized).
glm::vec2 GameController::GetMouseClickDirection() {
	// This function will update m_mouseClickDirection only while left mouse is currently pressed
	GLFWwindow* window = WindowController::GetInstance().GetWindow();
	if (!window) return m_mouseClickDirection;
			
	// Check left mouse button press
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		//CaptureMouseClickDirection();
	}

	return m_mouseClickDirection;
}

// Helper to prepare mesh when mode switches or reset requested
void GameController::PrepMesh(Mesh& _mesh, const std::string& _defaultName, bool _resetRequested) {
	if (m_modeSwitchTriggered) {
		ResetPos(2, _mesh);
		m_modelName = _defaultName;
	}
	if (_resetRequested) {
		ResetPos(2, _mesh);
	}
	m_mesh = &_mesh;
}

// New unified transform applier
void GameController::ApplyXforms(Mesh& _mesh, bool isMoveLight) {
	glm::vec2 d = GetMouseClickDirection() * 0.01f;

	// Sensitivities
	const float transXY = 0.0025f;
	const float rotXY = 0.05f;
	const float scaleXY = 0.0015f;
	const float transZ = 0.01f;
	const float rotZ = 0.2f;
	const float scaleZ = 0.000025f;

	// If caller is MoveLight, only allow position changes
	if (isMoveLight) {
		if (m_leftMouseClicked && m_translateEnabled) {
			glm::vec3 p = _mesh.GetPosition();
			p.x += d.x * transXY;
			p.y += d.y * transXY;
			_mesh.SetPosition(p);
		}
		if (m_middleMouseClicked && m_translateEnabled) {
			glm::vec3 p = _mesh.GetPosition();
			p.z += d.y * transZ;
			_mesh.SetPosition(p);
		}
		return;
	}

	// Full transform allowed for general models
	if (m_leftMouseClicked) {
		if (m_translateEnabled) {
			glm::vec3 p = _mesh.GetPosition();
			p.x += d.x * transXY;
			p.y += d.y * transXY;
			_mesh.SetPosition(p);
		}
		if (m_rotateEnabled) {
			glm::vec3 r = _mesh.GetRotation();
			r.x += d.y * rotXY;
			r.z += d.x * rotXY;
			_mesh.SetRotation(r);
		}
		if (m_scaleEnabled) {
			glm::vec3 s3 = _mesh.GetScale();
			s3.x += d.x * scaleXY * 0.001f;
			s3.y += d.y * scaleXY * 0.001f;
			_mesh.SetScale(s3);
		}
	}

	if (m_middleMouseClicked) {
		if (m_translateEnabled) {
			glm::vec3 p = _mesh.GetPosition();
			p.z += d.y * transZ;
			_mesh.SetPosition(p);
		}
		if (m_rotateEnabled) {
			glm::vec3 r = _mesh.GetRotation();
			r.y += d.x * rotZ;
			r.x += d.y * rotZ;
			_mesh.SetRotation(r);
		}
		if (m_scaleEnabled) {
			glm::vec3 s3 = _mesh.GetScale();
			s3.z += d.y * scaleZ * 0.01f;
			_mesh.SetScale(s3);
		}
	}
}

void GameController::UpdateMoveLight(Mesh& _mesh, GLFWwindow* _win, Fonts& _f) {
	PrepMesh(_mesh, "Fighter", m_resetLightPosPressed);

	ApplyXforms(_mesh, true);

	_mesh.Render(m_camera.GetProjection() * m_camera.GetView(), m_specularStrength, m_specularColor);

	MoveMeshWithMouse(Mesh::Lights[0], 0.00001f);

	for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
		Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
	}
}

string GameController::Vec3ToString(glm::vec3 _vec) {
	return "vec3(" + to_string(_vec.x) + ", " + to_string(_vec.y) + ", " + to_string(_vec.z) + ")";
}

void GameController::UpdateTransform(Mesh& _mesh, GLFWwindow* _win, Fonts& _f) {
	PrepMesh(_mesh, "Fighter", m_resetTransformPressed);

	ApplyXforms(_mesh, false);

	//rendering after applying transforms
	_mesh.Render(m_camera.GetProjection() * m_camera.GetView(), m_specularStrength, m_specularColor);

	for (unsigned int count = 0; count < Mesh::Lights.size(); count++) {
		Mesh::Lights[count].Render(m_camera.GetProjection() * m_camera.GetView());
	}
}

void GameController::ResetPos(int _option, Mesh& _mesh) {
	if (_option == 1) { //reset light pos
		_mesh.SetPosition({ 0.0f, 0.3f, 1.0f });
	}
	if (_option == 2) { //reset transformation
		_mesh.SetScale({ 0.0008f, 0.0008f, 0.0008f });
		_mesh.SetPosition({ 0.0f, 0.0f, 0.0f });
		_mesh.SetRotation({ 45.0f, 0.0f, 0.0f });
	}
}

void GameController::UpdateWaterScene(Mesh& _mesh, GLFWwindow* _win, Fonts& _f) {
	// Configure post-processor for this frame
	if (m_modeSwitchTriggered) {
		m_modelName = "Fish";
	}

	m_mesh = &_mesh;

	m_postProcessor.SetFrequencyAmplitude(m_frequency, m_amplitude);
	m_postProcessor.SetTime((float)glfwGetTime());
	m_postProcessor.SetTintBlue(m_tintBlueEnabled);

	// Render water mesh and lights
	_mesh.Render(m_camera.GetProjection() * m_camera.GetView(), m_specularStrength, m_specularColor);
	//for (unsigned int i = 0; i < Mesh::Lights.size(); ++i) {
	//	Mesh::Lights[i].Render(m_camera.GetProjection() * m_camera.GetView());
	//}

	m_postProcessor.SetWireFrame(m_wireframeEnabled);

}


void GameController::UpdateSpaceScene(Mesh& _mesh, GLFWwindow* _win, Fonts& _f) {
	if (m_modeSwitchTriggered) {
		_mesh.SetRotation({ 0.0f, 0.0f, 0.0f });
		m_modelName = "Fighter";
	}

	m_mesh = &_mesh;

	m_camera.Rotate();
	glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));
	m_skybox.Render(m_camera.GetProjection() * view);

	for (unsigned int count = 0; count < m_meshes.size(); count++) {
		m_meshes[count].Render(m_camera.GetProjection() * m_camera.GetView(), m_specularStrength, m_specularColor);
	}

	_mesh.Render(m_camera.GetProjection() * m_camera.GetView(), m_specularStrength, m_specularColor);
}

void GameController::MoveMeshWithMouse(Mesh& _mesh, float _sens) {
	//only move while left mouse is held
	if (!m_leftMouseClicked) return;

	//get the current mouse click direction (relative to center)
	glm::vec2 dir = GetMouseClickDirection();

	//converting screen-space delta to world-space translation factor
	//small sensitivity so movement isn't too fast

	//applying movement on X and Y axes (Y inverted already in CaptureMouseClickDirection)
	glm::vec3 pos = _mesh.GetPosition();
	pos.x += dir.x * _sens;
	pos.y += dir.y * _sens;
	_mesh.SetPosition(pos);
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

	m_shaderSkybox = Shader();
	m_shaderSkybox.LoadShaders("Skybox.vertexshader", "Skybox.fragmentshader");
#pragma endregion SetupShaders

#pragma region CreateMeshes
	// Create skybox using member m_skybox
	m_skybox.Create(&m_shaderSkybox, "../Assets/Models/Skybox.obj",
		{ "../Assets/Textures/Skybox/right.jpg",
		  "../Assets/Textures/Skybox/left.jpg",
		  "../Assets/Textures/Skybox/top.jpg",
		  "../Assets/Textures/Skybox/bottom.jpg",
		  "../Assets/Textures/Skybox/front.jpg",
		  "../Assets/Textures/Skybox/back.jpg" });


	// Create meshes
	Mesh m = Mesh();
	m.Create(&m_shaderColor, "../Assets/Models/Sphere.obj");
	m.SetPosition({ 0.0f, 0.3f, 1.0f });
	m.SetColor({ 1.0f, 1.0f, 1.0f });
	m.SetScale({ 0.0025f, 0.0025f, 0.0f });
	Mesh::Lights.push_back(m);

	//for (int i = 0; i < 1000; i++) {
	Mesh asteroid = Mesh();
	asteroid.Create(&m_shaderDiffuse, "../Assets/Models/asteroid.obj", 100);
	asteroid.SetCameraPosition(m_camera.GetPosition());
	asteroid.SetScale({ 0.1f, 0.1f, 0.1f });
	asteroid.SetPosition({ 0.0f, 0.0f, 0.0f });
	m_meshes.push_back(asteroid);
	//}

	Mesh fighter = Mesh();
	fighter.Create(&m_shaderDiffuse, "../Assets/Models/Fighter.obj");
	fighter.SetCameraPosition(m_camera.GetPosition());
	fighter.SetScale({ 0.0008f, 0.0008f, 0.0008f });
	fighter.SetPosition({ 0.0f, 0.0f, 0.0f });
	fighter.SetRotation({ 45.0f, 0.0f, 0.0f });
	//m_meshes.push_back(fighter);

	Mesh fish = Mesh();
	fish.Create(&m_shaderDiffuse, "../Assets/Models/Fish.obj");
	fish.SetCameraPosition(m_camera.GetPosition());
	fish.SetScale({ 0.02f, 0.02f, 0.02f });
	fish.SetPosition({ 0.0f, 0.0f, 0.0f });


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

	m_modelName = "Fighter";

	string modelStrPos = "";
	string leftBtnStr = "";
	string middleBtnStr = "";
	string modelStrRot = "";
	string modelStrScale = "";

	do
	{
		//updating stored tool window values
		m_moveLight = window->GetMoveLightValue();
		m_transform = window->GetTransformValue();
		m_waterScene = window->GetWaterSceneValue();
		m_spaceScene = window->GetSpaceSceneValue();

		//resetting flags (once pressed they remain true; storing as is)
		m_resetLightPosPressed = window->GetResetLightPosPressed();
		m_resetTransformPressed = window->GetResetTransformPressed();

		m_specularStrength = window->GetSpecularStrength();
		float specularColorR = (float)(window->GetSpecularColorR());
		float specularColorG = (float)(window->GetSpecularColorG());
		float specularColorB = (float)(window->GetSpecularColorB());

		m_frequency = (float)(window->GetFrequency());
		m_amplitude = (float)(window->GetAmplitude());

		m_translateEnabled = window->GetTranslateEnabled();
		m_rotateEnabled = window->GetRotateEnabled();
		m_scaleEnabled = window->GetScaleEnabled();
		m_wireframeEnabled = window->GetWireframeEnabled();
		m_tintBlueEnabled = window->GetTintBlueEnabled();


		m_specularColor = glm::vec3(specularColorR, specularColorG, specularColorB);



			// determine current mode index
			int currentMode = -1;
			if (m_moveLight) currentMode = 0;
			else if (m_transform) currentMode = 1;
			else if (m_waterScene) currentMode = 2;	
			else if (m_spaceScene) currentMode = 3;

			// one-shot trigger: fire once when mode changes
			if (currentMode != m_prevMode) {
				m_modeSwitchTriggered = true;
				m_prevMode = currentMode;
			} else {
				m_modeSwitchTriggered = false;
			}

			// Update mouse button states and capture direction accordingly
			UpdateOnLeftMouse();	
			UpdateOnMiddleMouse();

			//modelStrPos = "";
			//modelStrRot = "";
			//modelStrScale = "";

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the screen

			CaptureMouseClickDirection();

			// set tint only when in water scene and UI requests it
			if (m_waterScene && m_tintBlueEnabled) {
				m_postProcessor.SetTintBlue(true);
			} else {
				m_postProcessor.SetTintBlue(false);
			}

			m_postProcessor.Start();

			glm::mat4 view = glm::mat4(glm::mat3(m_camera.GetView()));

			//fighter.Render(m_camera.GetProjection() * m_camera.GetView());
			
			if (m_moveLight) {
				UpdateMoveLight(fighter, win, f);
			}
			else if (m_transform) {
				UpdateTransform(fighter, win, f);
			}
			else if (m_waterScene) {
				UpdateWaterScene(fish, win, f);
			}
			else if (m_spaceScene) {
				UpdateSpaceScene(fighter, win, f);
			}

			if (m_modeSwitchTriggered) {
				m_camera.Reset();
			}

		double currentTime = glfwGetTime();
		fps++;
		if (currentTime - lastTime >= 1.0) {
			fpsS = "FPS: " + to_string(fps);
			fps = 0;
			lastTime = currentTime;
		}
		
		// build model info strings safely
		if (m_mesh) {
			modelStrPos = m_modelName + " Position: " + Vec3ToString(m_mesh->GetPosition());
			modelStrRot = m_modelName + " Rotation: " + Vec3ToString(m_mesh->GetRotation());
			modelStrScale = m_modelName + " Scale: " + Vec3ToString(m_mesh->GetScale());
		} else {
			modelStrPos = m_modelName + " Position: (none)";
			modelStrRot = m_modelName + " Rotation: (none)";
			modelStrScale = m_modelName + " Scale: (none)";
		}

		leftBtnStr = "Left Mouse Button: " + string(m_leftMouseClicked ? "Down" : "Up");
		middleBtnStr = "Middle Mouse Button: " + string(m_middleMouseClicked ? "Down" : "Up");


		f.RenderText(fpsS, 100, 300, 0.5f, { 1.0f, 1.0f, 0.0f }); //font gets rendered IN the post processor for the final
		
		f.RenderText(leftBtnStr, 100, 330, 0.5f, { 1.0f, 1.0f, 0.0f });
		f.RenderText(middleBtnStr, 100, 360, 0.5f, { 1.0f, 1.0f, 0.0f });
		f.RenderText(modelStrPos, 100, 390, 0.5f, { 1.0f, 1.0f, 0.0f });
		f.RenderText(modelStrRot, 100, 420, 0.5f, { 1.0f, 1.0f, 0.0f });
		f.RenderText(modelStrScale, 100, 450, 0.5f, { 1.0f, 1.0f, 0.0f });

		// update post-processor globals only when in water scene
		if (m_waterScene) {
			m_postProcessor.SetTime((float)glfwGetTime());
			m_postProcessor.SetFrequencyAmplitude(m_frequency, m_amplitude);
		} else {
			// disable wave and tint outside water scene
			m_postProcessor.SetFrequencyAmplitude(0.0f, 0.0f);
			m_postProcessor.SetTime(0.0f);
			m_postProcessor.SetTintBlue(false);
		}

		m_postProcessor.End();

		// Ensure tint is cleared after rendering
		m_postProcessor.SetTintBlue(false);

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

