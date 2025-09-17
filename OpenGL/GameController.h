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
	int m_effect;

	Shader m_shader;
	Camera m_camera;
	Camera2 m_camera2;
	Mesh m_mesh;
};

#endif // GAME_CONTROLLER_H