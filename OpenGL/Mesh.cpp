#include "Mesh.h"
#include "Shader.h" // Add this include to resolve incomplete type error

Mesh::Mesh() {
	m_shader = nullptr;
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_world = glm::mat4(1.0f);
}

Mesh::~Mesh() {
}



void Mesh::Cleanup() {
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
}

void Mesh::Create(Shader* _shader) {
	m_shader = _shader;

	//m_vertexData = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f }; //this means 3 vertices, with 3 coordinates (x,y,z) each
	float a = 26.0f;
	float b = 42.0f;
	m_vertexData = {
		/*  Position  */  /*    RGBA Color    */
		-a, 0.0f, b,      1.0f, 0.0f, 0.0f, 1.0f, // Red
		a, 0.0f, b,       1.0f, 0.549f, 0.0f, 1.0f, // Orange 
		-a, 0.0f, -b,     1.0f, 1.0f, 0.0f, 1.0f, // Yellow
		a, 0.0f, -b,      1.0f, 1.0f, 0.0f, 1.0f, // Green??
		0.0f, b, a,       0.0f, 0.0f, 1.0f, 1.0f, // Blue
		0.0f, b, -a,      0.294f, 0.0f, 0.51f, 1.0f, // Indigo
		0.0f, -b, a,      0.502f, 0.0f, 0.502f, 1.0f, // Purple
		0.0f, -b, -a,     1.0f, 1.0f, 1.0f, 1.0f, // White
		b, a, 0.0f,       0.0f, 1.0f, 1.0f, 1.0f, // Cyan
		-b, a, 0.0f,      0.0f, 0.0f, 0.0f, 1.0f, // Black
		b, -a, 0.0f,      0.118f, 0.565f, 1.0f, 1.0f, // Dodger blue
		-b, -a, 0.0f,     0.863f, 0.078f, 0.235f, 1.0f // Crimson
	};

	glGenBuffers(1, &m_vertexBuffer); //generating 1 buffer, which is a vertex buffer, meaning it holds vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //binding the buffer so that we can use it as an array buffer for our vertices
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW); //uploading the data from m_vertexData to the GPU. We call this whenever the data changes.

	m_indexData = {
		0, 6, 1, 0 ,11, 6, 1, 4, 0, 1, 8, 4,
		1, 10, 8, 2, 5, 3, 2, 9, 5, 2, 11, 9,
		3, 7, 2, 3, 10, 7, 4, 8, 5, 4, 9, 0,
		5, 8, 3, 5, 9, 4, 6, 10, 1, 6, 11, 7,
		7, 10, 6, 7, 11, 2, 8, 10, 3, 9, 11, 0
	};
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLubyte), m_indexData.data(), GL_STATIC_DRAW);
	//NEW. MAY NEED TO DELETE.
	m_world = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 0.0f));
}

void Mesh::Render(glm::mat4 _wvp) {
	glUseProgram(m_shader->GetProgramID()); // Use our shader



	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attirbute we want to configure
		3, //size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		7 * sizeof(float), // stride (7 floats per vertex definition)
		(void*)0); // array buffer offset

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(m_shader->GetAttrColors(), // The attirbute we want to configure
		4, //size (4 components per color value
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		7 * sizeof(float), // stride (7 floats per vertex definition)
		(void*)(3 * sizeof(float))); // array buffer offset
	
	//saving the position as a vec 3
	glm::vec3 position = glm::vec3(m_world[3]); //column 3 holds translation in glm::mat4

	//creating incremental rotation around Y-axis
	glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), 0.001f, glm::vec3(0.0f, 1.0f, 0.0f));

	//translating to origin, rotating, then translating back to original position
	glm::mat4 toOrigin = glm::translate(glm::mat4(1.0f), -position);
	glm::mat4 positionMat = glm::translate(glm::mat4(1.0f), position);

	//applying rotation around current position
	m_world = positionMat * rotation * toOrigin * m_world;

	


	_wvp *= m_world;
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // Bind the vertex buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer); // Bind the index buffer
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &_wvp[0][0]);
	//glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 7); // Draw the triangle
	glDrawElements(GL_TRIANGLES, m_indexData.size(), GL_UNSIGNED_BYTE, (void*)0);
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
}