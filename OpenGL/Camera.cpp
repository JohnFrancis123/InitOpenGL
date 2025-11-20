#include "Camera.h"

Camera::Camera() {
	m_projection = { };
	m_view = { };
	m_position = { };
	m_lookAt = glm::vec3();
	m_rotation = glm::vec3();
	m_angle = 0;
}

Camera::Camera(Resolution _screenResolution) {
	m_position = {3, 3, 3};
	m_lookAt = { 0, 0, 0 };
	m_rotation = { 0, 0, 0 };
	m_angle = 0;
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

void Camera::Rotate() {
	//m_angle += 0.01f;
	//m_lookAt.x = cos(glm::radians(m_angle)) * 100;
	//m_lookAt.z = sin(glm::radians(m_angle)) * 100;

	// Camera matrix
	m_view = glm::lookAt(
		m_position, // Camera is at (0, 0, 0), in World Space
		m_lookAt, 
		glm::vec3(0, 1, 0)); // Head is up (set to 0, -1, 0, to look upside down)
}

Camera::~Camera() {
}