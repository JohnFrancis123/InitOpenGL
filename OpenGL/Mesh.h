#ifndef MESH_H
#define MESH_H

#include "StandardIncludes.h"
#include "Texture.h"

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

	glm::vec3 ToYuv(glm::vec3(_rgb));
	glm::vec3 ToRgb(glm::vec3(_yuv));

	void Render(glm::mat4 _wvp);

private:
	Shader* m_shader; //the shader that will be used to render this mesh
	Texture m_texture;
	Texture m_texture2;
	GLuint m_vertexBuffer; //this is held on the VRAM
	GLuint m_indexBuffer; // GPU buffer
	std::vector<GLfloat> m_vertexData; // Store vertex data in RAM
	std::vector<GLubyte> m_indexData; // Store index data in RAM
	glm::vec3 m_position;
	glm::vec3 m_rotation;


	//glm::mat4 m_world;
};

#endif // MESH_H