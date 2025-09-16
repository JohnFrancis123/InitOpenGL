#include "Mesh.h"
#include "Shader.h" // Add this include to resolve incomplete type error

Mesh::Mesh() {
	m_shader = nullptr;
	m_vertexBuffer = 0;
}

Mesh::~Mesh() {
}

void Mesh::Create(Shader* _shader) {
	m_shader = _shader;

	m_vertexData = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f }; //this means 3 vertices, with 3 coordinates (x,y,z) each
	
	glGenBuffers(1, &m_vertexBuffer); //generating 1 buffer, which is a vertex buffer, meaning it holds vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //binding the buffer so that we can use it as an array buffer for our vertices
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW); //uploading the data from m_vertexData to the GPU. We call this whenever the data changes.
}

void Mesh::Cleanup() {
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render(glm::mat4 _wvp) {
	glUseProgram(m_shader->GetProgramID()); // Use our shader



	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attirbute we want to configure
		3, //size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		0, // stride
		(void*)0); // array buffer offset

	_wvp *= m_world;
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);
	// Draw the Traingle
	glDrawArrays(GL_TRIANGLES, 0, 3); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
}