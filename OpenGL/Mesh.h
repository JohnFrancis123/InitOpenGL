#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
class Shader;

class Mesh
{
public:
	// Constructors / Destructors
	Mesh();
	virtual ~Mesh();

	// Methods
	void Create(Shader* _shader);
	void Cleanup();
	void Render(glm::mat4 _wvp);

private:
	Shader* m_shader; //the shader that will be used to render this mesh
	GLuint m_vertexBuffer; //this is held on the VRAM
	GLuint m_indexBuffer; // GPU buffer
	std::vector<GLfloat> m_vertexData; // Store vertex data in RAM
	std::vector<GLubyte> m_indexData; // Store index data in RAM
	glm::mat4 m_world;
};

#endif // MESH_H