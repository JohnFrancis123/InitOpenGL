#include "Camera.h"

Camera::Camera() {
	m_projection = { };
	m_view = { };
	m_position = { };
}

Camera::Camera(Resolution _screenResolution) {
	m_position = { 4, 1, 2 };
	// Projection Matrix : 45 deg FOV, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	m_projection = glm::perspective(glm::radians(45.0f), // 0.3 degree FOV to accomodate for the distance. Creating a zoom effect.
									(float)_screenResolution.m_width /
									(float)_screenResolution.m_height,
									0.1f,
									1000.0f);

	// Or for an ortho camera: 
	//glm::mat4 Projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f); // In world coordinates

	// Camera Matrix
	m_view = glm::lookAt(
		m_position, // where the Camera is, in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)); // Head is up (set to 0, -1, 0, to look upside down)
}

Camera::~Camera() {
}