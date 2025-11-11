#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "Skybox.h"
#include "WindowController.h"
#include "Camera.h"
#include "Fonts.h"
//#include "Camera2.h"

class GameController : public Singleton<GameController>
{
public:
		// Constructors / Destructors
	GameController();
	virtual ~GameController(); 
	//Methods
	void Initialize();
	void RunGame();
private:
	Shader m_shaderColor;
	Shader m_shaderDiffuse;
	Shader m_shaderFont;
	Shader m_shaderSkybox;
	Camera m_camera;
	vector<Mesh> m_meshBoxes;
	Mesh m_meshLight;
	Skybox m_skybox;
};

#endif // GAME_CONTROLLER_H