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

	// Accessors
	void SetPosition(glm::vec3 _position) { m_position = _position; }
	glm::vec3 GetPosition() { return  m_position; }
	void SetScale(glm::vec3 _scale) { m_scale = _scale; }
	void SetColor(glm::vec3 _color) { m_color = _color; }
	glm::vec3 GetColor() { return m_color; }
	void SetLightPosition(glm::vec3 _lightPosition) { m_lightPosition = _lightPosition; }
	void SetLightColor(glm::vec3 _lightcolor) { m_lightColor = _lightcolor; }
	void SetCameraPosition(glm::vec3 _cameraPosition) { m_cameraPosition = _cameraPosition; }

	// Methods
	void Create(Shader* _shader, string _file);
	void Cleanup();
	void CalculateTransform();
	void Render();
	void Render(glm::mat4 _wvp);

	// Members
	static vector<Mesh> Lights;
private:
	// Methods
	void SetShaderVariables(glm::mat4 _pv);
	void BindAttributes();
	string Concat(string _s1, int _index, string _s2);
	string RemoveFolder(string _map);

	// Members
	Shader* m_shader; //the shader that will be used to render this mesh
	Texture m_textureSpecular;
	Texture m_textureDiffuse;
	Texture m_textureNormal;

	//Texture m_texture;
	//Texture m_texture2;

	GLuint m_vertexBuffer; //this is held on the VRAM
	GLuint m_indexBuffer; // GPU buffer
	std::vector<GLfloat> m_vertexData; // Store vertex data in RAM
	std::vector<GLubyte> m_indexData; // Store index data in RAM
	bool m_enableNormalMap;

	// Transform
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_world;

	// Lights
	glm::vec3 m_lightPosition;
	glm::vec3 m_lightColor;
	glm::vec3 m_cameraPosition;
	glm::vec3 m_color;
	//glm::mat4 m_world;
};

#endif // MESH_H