#ifndef POSTPROCESSOR_H
#define POSTPROCESSOR_H

#include "StandardIncludes.h"
#include "Texture.h"

class Shader;

class PostProcessor
{
public:
	// Constructors / Destructors
	PostProcessor();
	virtual ~PostProcessor();

	// Methods
	void Create(Shader* _postShader);
	void Cleanup();
	void Start();
	void End();

private:
	// Members
	GLuint m_frameBuffer;
	GLuint m_textureColorBuffer;
	GLuint m_renderBufferObject;
	GLuint m_vertexBuffer;
	Shader* m_postShader;

	// Methods
	void CreateVertices();
	void CreateBuffers();
	void BindVertices();
};
#endif // POSTPROCESSOR_H