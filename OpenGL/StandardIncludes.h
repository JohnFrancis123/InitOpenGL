#ifndef STANDARD_INCLUDES_H
#define STANDARD_INCLUDES_H

// include standard headers
#include <vector> //same as a list, but implemented as a dynamic array

#ifdef _WIN32
#include <Windows.h>
#define M_ASSERT(_cond, _msg) \
	if(!(_cond)) {OutputDebugStringA(_msg); std::abort(); glfwTerminate(); } 
#endif 

// Openg GL/Helper headers
#include <GL/glew.h> //Include GLEW
#include <GLFW/glfw3.h> //Include GLFW
#include <glm/glm.hpp> //Include GLM

#include "Singleton.h"

using namespace std;

#endif // STANDARD_INCLUDES_H