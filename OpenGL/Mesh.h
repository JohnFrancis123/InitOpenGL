#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"

class Mesh
{
public:
	// Constructors / Destructors
	Mesh();
	virtual ~Mesh();

	// Methods
	void Create();
	void Cleanup();
	void Render();

private:
	GLuint m_vertexBuffer; //this is held on the VRAM
	std::vector<GLfloat> m_vertexData; //this is held on the RAM
};

#endif // MESH_H