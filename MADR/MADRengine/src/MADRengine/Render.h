#pragma once
#include "MADRengine/MADRpch.h"
#include "glad.h"
#include "glfw3.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

GLFWwindow** RenderStartup();
void RenderUpdate(GLFWwindow*);