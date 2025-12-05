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
	void SetFrequencyAmplitude(float freq, float amp) { m_frequency = freq; m_amplitude = amp; }
	void SetTime(float t) { m_time = t; }
	void SetTintBlue(bool v) { m_tintBlue = v; }

	void SetWireFrame(bool _wireFrame) { m_wireFrame = _wireFrame; }

private:
	// Members
	GLuint m_frameBuffer;
	GLuint m_textureColorBuffer;
	GLuint m_renderBufferObject;
	GLuint m_vertexBuffer;
	Shader* m_postShader;
	float m_frequency = 1.0f;
	float m_amplitude = 0.01f;
	float m_time = 0.0f;
	bool m_tintBlue = false;

	bool m_wireFrame;

	// Methods
	void CreateVertices();
	void CreateBuffers();
	void BindVertices();
};
#endif // POSTPROCESSOR_H