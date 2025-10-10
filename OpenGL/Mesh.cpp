#include "Mesh.h"
#include "Shader.h" // Add this include to resolve incomplete type error

Mesh::Mesh() {
	m_shader = nullptr;
	m_texture = { };
	m_texture2 = { };
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_position = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
}

Mesh::~Mesh() {
}

void Mesh::Cleanup() {
	glDeleteBuffers(1, &m_indexBuffer);
	glDeleteBuffers(1, &m_vertexBuffer);
	m_texture.Cleanup();
	m_texture2.Cleanup();
}

void Mesh::Create(Shader* _shader) {
	m_shader = _shader;

	m_texture = Texture();
	m_texture.LoadTexture("../Assets/Textures/Wood.jpg");
	m_texture2 = Texture();
	m_texture2.LoadTexture("../Assets/Textures/Emoji.jpg");

	m_vertexData = {
		/*    Position   */  /*  RGB Color  */   /* Texture coords */
		50.0f, 50.0f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // top-right
		50.0f, -50.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // bottom-right
		-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  // bottom-left
		-50.0f, 50.0f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f   //top-left
	};

	glGenBuffers(1, &m_vertexBuffer); //generating 1 buffer, which is a vertex buffer, meaning it holds vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //binding the buffer so that we can use it as an array buffer for our vertices
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW); //uploading the data from m_vertexData to the GPU. We call this whenever the data changes.

	m_indexData = {
		2, 0, 3, 2, 1, 0
	};
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLubyte), m_indexData.data(), GL_STATIC_DRAW);

}

void Mesh::Render(glm::mat4 _wvp, glm::vec3 _yuv, bool inverted) {

	glUseProgram(m_shader->GetProgramID()); // Use our shader
	
	glUniform3f(m_shader->GetYUV(), _yuv.x, _yuv.y, _yuv.z); //passing _yuv into the fragment shader
	glUniform1i(m_shader->GetInverted(), inverted); //passing invert to the fragment shader

	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attirbute we want to configure
		3, //size (3 vertices per primitive)
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		8 * sizeof(float), // stride (8 floats per vertex definition)
		(void*)0); // array buffer offset

	// 2nd attribute buffer : colors
	glEnableVertexAttribArray(m_shader->GetAttrColors());
	glVertexAttribPointer(m_shader->GetAttrColors(), // The attirbute we want to configure
		3, //size (3 components per color value
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		8 * sizeof(float), // stride (7 floats per vertex definition)
		(void*)(3 * sizeof(float))); // array buffer offset
	
	// 3rd attirbute buffer : texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoord());
	glVertexAttribPointer(m_shader->GetAttrTexCoord(), // The attribute we want to configure
		2, //size (3 vertices per primitive). SHOULD PROBABLY SET TO 3.
		GL_FLOAT, //type
		GL_FALSE, //normalized?
		8 * sizeof(float), //stride (8 floats per vertex definition)
		(void*)(6 * sizeof(float))); // array buffer offset

	//4th attribute: WVP
	glm::mat4 transform = glm::rotate(_wvp, m_rotation.y, glm::vec3(0, 1, 0));
	glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &transform[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // Bind the vertex buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer); // Bind the index buffer
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetTexture());
	glUniform1i(m_shader->GetSampler1(), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture2.GetTexture());
	glUniform1i(m_shader->GetSampler2(), 1);
	
	glDrawElements(GL_TRIANGLES, m_indexData.size(), GL_UNSIGNED_BYTE, (void*)0);
	glDisableVertexAttribArray(m_shader->GetAttrColors());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoord());
}

