#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"
#include "Shader.h"
#include "Mesh.h"
#include "WindowController.h"
#include "Camera.h"
#include "Camera2.h"

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
	Camera m_camera;
	Mesh m_meshBox;
	Mesh m_meshLight;
};

#endif // GAME_CONTROLLER_H