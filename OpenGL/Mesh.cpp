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
	m_scale = { 1, 1, 1 };
	m_world = glm::mat4();
	m_lightPosition = { 0, 0 ,0 };
	m_cameraPosition = { 0, 0 ,0 };
	m_lightColor = { 1, 1, 1 };
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
		/* Position */ /* Normals */ /* Texture Coords
		*/
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
	};

	glGenBuffers(1, &m_vertexBuffer); //generating 1 buffer, which is a vertex buffer, meaning it holds vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //binding the buffer so that we can use it as an array buffer for our vertices
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW); //uploading the data from m_vertexData to the GPU. We call this whenever the data changes.

	//glGenBuffers(1, &m_indexBuffer);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLubyte), m_indexData.data(), GL_STATIC_DRAW);
	//NEW. MAY NEED TO DELETE.
	//m_world = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 0.0f));
}

void Mesh::Render(glm::mat4 _wvp) {
	glUseProgram(m_shader->GetProgramID()); // Use our shader

	CalculateTransform();
	SetShaderVariables(_wvp);
	BindAttributes();



	//m_shader->SetVec3("AmbientLight", { 0.1f, 0.1f, 0.1f });
	//m_shader->SetVec3("DiffuseColor", { 1.0f, 1.0f, 1.0f });
	//m_shader->SetVec3("LightDirection", { 1.0f, 0.5f, 0.0f });
	//m_shader->SetVec3("LightColor", { 0.5f, 0.9f, 0.5f });
	
	//glBindTexture(GL_TEXTURE_2D, m_texture.GetTexture());
	//glBindTexture(GL_TEXTURE_2D, m_texture2.GetTexture()); //

	glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 8); // Draw the triangle
	glDrawElements(GL_TRIANGLES, m_indexData.size(), GL_UNSIGNED_BYTE, (void*)0);
	glDisableVertexAttribArray(m_shader->GetAttrNormals());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoords());
}

void Mesh::CalculateTransform() {
	m_world = glm::translate(glm::mat4(1.0f), m_position);
	m_world = glm::rotate(m_world, m_rotation.y, glm::vec3(0, 1, 0));
	m_world = glm::scale(m_world, m_scale);
}

void Mesh::SetShaderVariables(glm::mat4 _pv) {
	m_shader->SetMat4("World", m_world);
	m_shader->SetVec3("AmbientLight", { 0.1f, 0.1f, 0.1f });
	m_shader->SetVec3("DiffuseColor", { 1.0f, 1.0f, 1.0f });
	m_shader->SetFloat("SpecularStrength", 4);
	m_shader->SetVec3("SpecularColor", { 3.0f, 0.0f, 0.0f });
	m_shader->SetVec3("LightPosition", m_lightPosition);
	m_shader->SetVec3("LightColor", m_lightColor);
	m_shader->SetMat4("WVP", _pv * m_world);
	m_shader->SetVec3("CameraPosition", m_cameraPosition);
}

void Mesh::BindAttributes() {

	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(m_shader->GetAttrVertices());
	glVertexAttribPointer(m_shader->GetAttrVertices(), // The attirbute we want to configure
		3, //size (3 vertices per primitive)
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		8 * sizeof(float), // stride (8 floats per vertex definition)
		(void*)0); // array buffer offset

	// 2nd attribute buffer : normals
	glEnableVertexAttribArray(m_shader->GetAttrNormals());
	glVertexAttribPointer(m_shader->GetAttrNormals(),
		3, // size
		GL_FLOAT, // type
		GL_FALSE, // normalized?
		8 * sizeof(float), // stride (8 floats per vertex definition)
		(void*)(3 * sizeof(float))); // array buffer offset

	// 3rd attirbute buffer : texCoords
	glEnableVertexAttribArray(m_shader->GetAttrTexCoords());
	glVertexAttribPointer(m_shader->GetAttrTexCoords(), // The attribute we want to configure
		2, //size (3 vertices per primitive). SHOULD PROBABLY SET TO 3.
		GL_FLOAT, //type
		GL_FALSE, //normalized?
		8 * sizeof(float), //stride (8 floats per vertex definition)
		(void*)(6 * sizeof(float))); // array buffer offset

	////4th attribute: WVP
	//m_rotation.y += 0.001f;
	//glm::mat4 transform = glm::rotate(_wvp, m_rotation.y, glm::vec3(0, 1, 0));
	//glUniformMatrix4fv(m_shader->GetAttrWVP(), 1, GL_FALSE, &transform[0][0]);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); // Bind the vertex buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer); // Bind the index buffer

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture.GetTexture());
	glUniform1i(m_shader->GetSampler1(), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture2.GetTexture());
	glUniform1i(m_shader->GetSampler2(), 1);
}