
#include "Render.h"
GLFWwindow* rWindow;
#define Background_Color 0.2f, 0.3f, 0.3f, 1.0f

GLFWwindow** RenderStartup()
{
	if (glfwInit()) 
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		rWindow = glfwCreateWindow(1920, 1080, "TestWindow", NULL, NULL);
		if (rWindow != NULL)
		{


			glfwMakeContextCurrent(rWindow);


			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
				std::cerr << "GLAD failed to initialize\n";
		}
	}

	return &rWindow;
}

void RenderUpdate(GLFWwindow* window)
{


	glClearColor(Background_Color);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glfwSwapBuffers(rWindow);
	glFlush();
	glfwPollEvents();
}
