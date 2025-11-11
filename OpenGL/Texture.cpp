#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture() {
	m_width = 0;
	m_height = 0;
	m_channels = 0;
	m_texture = 0;
}


void Texture::Cleanup() {
	glDeleteTextures(1, &m_texture);
}

void Texture::LoadTexture(string _fileName) {
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	//repeat wrapping
	// Set the texture wrapping/filtering options (on the currently bound texture
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Load and generate the texture
	stbi_set_flip_vertically_on_load(true);
	GLubyte* data = stbi_load(_fileName.c_str(), &m_width, &m_height, &m_channels, 0); //stbi will RETURN the width, height, and channels into these variables..
	M_ASSERT(data != nullptr, "Failed to load texture");
	//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	
	if (EndsWith(_fileName, ".png")) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	glGenerateMipmap(GL_TEXTURE_2D);

	// Free image data from RAM
	stbi_image_free(data);
}

bool Texture::EndsWith(const std::string& _str, const std::string& _suffix) {
	// 1. Check if the suffix is longer than the main string. 
	// If it is, the main string cannot end with the suffix.
	if (_suffix.size() > _str.size()) {
		return false;
	}

	// 2. Compare the trailing part of _str with _suffix.
	// The compare function is used to compare a substring of _str 
	// starting at a specific position with the entire _suffix.

	// Starting position: _str.size() - _suffix.size()
	// This calculates the index in _str where the suffix must start.

	// Length of substring to compare: _suffix.size()
	// This is the length of the suffix.

	// The string to compare against: _suffix

	// std::string::compare returns 0 if the strings are equal.
	return _str.compare(_str.size() - _suffix.size(), _suffix.size(), _suffix) == 0;
}