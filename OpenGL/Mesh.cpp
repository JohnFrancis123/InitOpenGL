#include "Mesh.h"

Mesh::Mesh() {
	m_vertexBuffer = 0;
}

Mesh::~Mesh() {
}

void Mesh::Create() {
	m_vertexData = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f }; //this means 3 vertices, with 3 coordinates (x,y,z) each
	glGenBuffers(1, &m_vertexBuffer); //generating 1 buffer, which is a vertex buffer, meaning it holds vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //binding the buffer so that we can use it as an array buffer for our vertices
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW); //uploading the data from m_vertexData to the GPU. We call this whenever the data changes.
}

void Mesh::Cleanup() {
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Render() {
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(0, 3/*size*/, GL_FLOAT /*type*/, GL_FALSE /*normalized?*/, 0/*stride*/, (void*)0/*offset*/);
	// Draw the Traingle
	glDrawArrays(GL_TRIANGLES, 0, 3); //starting from vertex 0; 3 vertices = 1 triangle
	glDisableVertexAttribArray(0);
}