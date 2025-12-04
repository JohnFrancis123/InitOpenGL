#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Skybox.h"
#include "WindowController.h"
#include "Camera.h"
#include "Fonts.h"
#include "PostProcessor.h"
//#include "Camera2.h"
 //
class GameController : public Singleton<GameController>
{
public:
		// Constructors / Destructors
	GameController();
	virtual ~GameController(); 
	//Methods
	void Initialize();
	void RunGame();

	// Returns the last mouse-click direction (stored in m_mouseClickDirection). Calls will update this when a click occurs.
	glm::vec2 GetMouseClickDirection();
	// Simple getter to retrieve the stored mouse click direction without changing it
	glm::vec2 GetStoredMouseClickVector() const		{ return m_mouseClickDirection; }

	// Update functions for mouse buttons; call these from your update loop
	void UpdateOnLeftMouse();
	void UpdateOnMiddleMouse();

	void UpdateMoveLight(Mesh& _mesh, GLFWwindow* _win, Fonts& _f);
	void UpdateTransform(Mesh& _mesh, GLFWwindow* _win, Fonts& _f);
	void UpdateWaterScene(Mesh& _mesh, GLFWwindow* _win, Fonts& _f);
	void UpdateSpaceScene(Mesh& _mesh, GLFWwindow* _win, Fonts& _f);

	void MoveMeshWithMouse(Mesh& _mesh, float _sens);

private:
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderPost;
	Shader m_shaderSkybox;
	Camera m_camera;
	PostProcessor m_postProcessor;
	vector<Mesh> m_meshes;
	Mesh m_meshLight;
	Skybox m_skybox;
	GLuint vao;

	// Stored tool window values
	bool m_moveLight = false;
	bool m_transform = false;
	bool m_waterScene = false;
	bool m_spaceScene = false;
	bool m_resetLightPosPressed = false;
	bool m_resetTransformPressed = false;

	int m_specularStrength = 0;
	float m_specularColorR = 1.0f;
	float m_specularColorG = 1.0f;
	float m_specularColorB = 1.0f;
	float m_frequency = 0.0f;
	float m_amplitude = 0.0f;

	bool m_translateEnabled = false;
	bool m_rotateEnabled = false;
	bool m_scaleEnabled = false;
	bool m_wireframeEnabled = false;
	bool m_tintBlueEnabled = false;

	// Mouse click direction stored as vector relative to screen center (not normalized)
	glm::vec2 m_mouseClickDirection = glm::vec2(0.0f, 0.0f);

	// Mouse button state flags
	bool m_leftMouseClicked = false;
	bool m_middleMouseClicked = false;

	bool m_currState[4];
	bool m_changed = false;
	// one-shot mode switch tracking
	int m_prevMode = -1; // -1 = none, 0=moveLight,1=transform,2=water,3=space
	bool m_modeSwitchTriggered = false;
	// Helper to capture cursor vector relative to center

	glm::vec3 m_specularColor;
	void CaptureMouseClickDirection();
};

#endif // GAME_CONTROLLER_H