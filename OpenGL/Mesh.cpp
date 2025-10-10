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
	//m_world = glm::mat4(1.0f);
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

	//m_vertexData = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f }; //this means 3 vertices, with 3 coordinates (x,y,z) each
	float a = 26.0f;
	float b = 42.0f;
	m_vertexData = {
		/*    Position   */  /*  RGB Color  */   /* Texture coords */
		50.0f, 50.0f, 0.0f,   1.0f, 0.0f, 0.0f,  1.0f, 1.0f,  // top-right
		50.0f, -50.0f, 0.0f,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,  // bottom-right
		-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 1.0f,  0.0f, 0.0f,  // bottom-left
		-50.0f, 50.0f, 0.0f,  1.0f, 1.0f, 1.0f,  0.0f, 1.0f   //top-left
	};

	//m_vertexData = {
	//	/*    Position   */  /*  RGB Color  */   /* Texture coords */
	//	50.0f, 50.0f, 0.0f,   0.5f, 0.0f, 0.0f,  1.0f, 1.0f,  // top-right
	//	50.0f, -50.0f, 0.0f,  0.0f, 0.5f, 0.0f,  1.0f, 0.0f,  // bottom-right
	//	-50.0f, -50.0f, 0.0f, 0.0f, 0.0f, 0.5f,  0.0f, 0.0f,  // bottom-left
	//	-50.0f, 50.0f, 0.0f,  0.5f, 0.5f, 0.5f,  0.0f, 1.0f   //top-left
	//};

	glGenBuffers(1, &m_vertexBuffer); //generating 1 buffer, which is a vertex buffer, meaning it holds vertices
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer); //binding the buffer so that we can use it as an array buffer for our vertices
	glBufferData(GL_ARRAY_BUFFER, m_vertexData.size() * sizeof(float), m_vertexData.data(), GL_STATIC_DRAW); //uploading the data from m_vertexData to the GPU. We call this whenever the data changes.

	m_indexData = {
		2, 0, 3, 2, 1, 0
	};
	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexData.size() * sizeof(GLubyte), m_indexData.data(), GL_STATIC_DRAW);
	//NEW. MAY NEED TO DELETE.
	//m_world = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 100.0f, 0.0f));
}

void Mesh::Render(glm::mat4 _wvp, glm::vec3 _yuv) {

	glUseProgram(m_shader->GetProgramID()); // Use our shader
	
	glUniform3f(m_shader->GetUniYUV(), _yuv.x, _yuv.y, _yuv.z);
	//

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
	//m_rotation.y += 0.001f;
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
	
	//glBindTexture(GL_TEXTURE_2D, m_texture.GetTexture());
	//glBindTexture(GL_TEXTURE_2D, m_texture2.GetTexture()); //

	//glDrawArrays(GL_TRIANGLES, 0, m_vertexData.size() / 7); // Draw the triangle
	glDrawElements(GL_TRIANGLES, m_indexData.size(), GL_UNSIGNED_BYTE, (void*)0);
	glDisableVertexAttribArray(m_shader->GetAttrColors());
	glDisableVertexAttribArray(m_shader->GetAttrVertices());
	glDisableVertexAttribArray(m_shader->GetAttrTexCoord());
}

glm::vec3 Mesh::ToYuv(glm::vec3 _rgb) {
	glm::vec3 yuv = { 0.0f, 0.0f ,0.0f };
	glm::mat3 yuvMat = { 
		{0.299f, 0.587f, 0.114f},
		{-0.14713f, -0.28886f, 0.436f},
		{0.615f, -0.514999f, -0.10001f} 
	};
	yuv = _rgb * yuvMat;
	return yuv;
}

glm::vec3 Mesh::ToRgb(glm::vec3 _yuv) {
	glm::vec3 rgb = { 0.0f, 0.0f ,0.0f };
	glm::mat3 rgbMat = { 
		{1.0f, 0.0f, 1.13983f},
		{1.0f, -0.39465f ,-5.8060f},
		{1.0f, 2.03211f, 0.0f}
	};
	rgb = _yuv * rgbMat;
	return rgb;
}