#include "PostProcessor.h"
#include "WindowController.h"
#include "Shader.h"

PostProcessor::PostProcessor()
{
	m_frameBuffer = 0;
	m_textureColorBuffer = 0;
	m_renderBufferObject = 0;
	m_vertexBuffer = 0;
	m_postShader = 0; //nullptr???
}

PostProcessor::~PostProcessor()
{
}

void PostProcessor::Cleanup() {
	glDeleteFramebuffers(1, &m_frameBuffer);
	glDeleteTextures(1, &m_textureColorBuffer);
	glDeleteRenderbuffers(1, &m_renderBufferObject);
}

void PostProcessor::Create(Shader* _postShader) {
	m_postShader = _postShader;
	CreateBuffers();
	CreateVertices();
	//BindVertices();
}

void PostProcessor::CreateBuffers() {
	// Framebuffer Configuration
	glGenFramebuffers(1, &m_frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);

	// Create a color attachment texture
	glGenTextures(1, &m_textureColorBuffer);
	glBindTexture(GL_TEXTURE_2D, m_textureColorBuffer);
	Resolution r = WindowController::GetInstance().GetResolution();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, r.m_width, r.m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorBuffer, 0);

	// Create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, r.m_width, r.m_height); // Use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject); // now actually attach it

	// Now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	M_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete!");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void PostProcessor::CreateVertices() {
	float vertexData[] = { // Vertex attributes for a quad that fills
						   // the entire screen in Normalized Device Coordinates.
		// positions   // texCoords
		-1.0f,  1.0f,  0.0f, 1.0f,
		-1.0f, -1.0f,  0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,

		-1.0f,  1.0f,  0.0f, 1.0f,
		 1.0f, -1.0f,  1.0f, 0.0f,
		 1.0f,  1.0f,  1.0f, 1.0f
	};

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), &vertexData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void PostProcessor::BindVertices() {
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // Bind the Vertex Buffer
	
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(m_postShader->GetAttrVertices());
	glVertexAttribPointer(m_postShader->GetAttrVertices(), //the attribute we want to configure
		2,                  // size (2 components
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		4 * sizeof(float),  // stride floats per vertex definition
		(void*)0            // array buffer offset
	);

	glEnableVertexAttribArray(m_postShader->GetAttrTexCoords());
	glVertexAttribPointer(m_postShader->GetAttrTexCoords(), //the attribute we want to configure
		2,                  // size (2 components
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		4 * sizeof(float),  // stride floats per vertex definition
		(void*)(2 * sizeof(float)));  // array buffer offset
}

void PostProcessor::Start() {
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
}

void PostProcessor::End() {
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glDisable(GL_DEPTH_TEST); // Disable depth test so screen-space quad isn't discarded due to depth test.

	glUseProgram(m_postShader->GetProgramID()); // Use our shader
	m_postShader->SetTextureSampler("ScreenTexture", GL_TEXTURE0, 0, m_textureColorBuffer);
	BindVertices();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // remove this when done output 2
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDisableVertexAttribArray(m_postShader->GetAttrVertices());
	glDisableVertexAttribArray(m_postShader->GetAttrTexCoords());
}