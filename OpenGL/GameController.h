#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "StandardIncludes.h"
#include "Mesh.h"

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
	Mesh m_mesh;
};

#endif // GAME_CONTROLLER_H