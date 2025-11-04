//#include "Camera2.h"
//
//Camera2::Camera2() {
//	m_projection = { };
//	m_view = { };
//}
//
//Camera2::Camera2(Resolution _screenResolution) {
//	//camera view matrix 2
//	m_view = glm::lookAt(
//		glm::vec3(5, 6, 6), // Camera is at (5, 6, 6), in World Space
//		glm::vec3(0, 0, 0), // and looks at the origin
//		glm::vec3(0, -1, 0)); //upside down
//
//	//camera projection matrix 2
//	m_projection = glm::perspective(glm::radians(75.0f), //changed FOV to 75 degrees for mild fisheye effect
//		(float)_screenResolution.m_width /
//		(float)_screenResolution.m_height,
//		0.1f,
//		1000.0f);
//}
//
//Camera2::~Camera2() {
//}