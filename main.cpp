#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <windows.h>
#include <iostream>
#include "game.h"
#include "resource_manage.h"


Game SpaceWar;
const int SCREEN_WIDTH = GetSystemMetrics(SM_CXFULLSCREEN) * 0.8;
const int SCREEN_HEIGHT = GetSystemMetrics(SM_CYFULLSCREEN) * 0.8;
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);


int main(int argc, char *argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Explorer", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	GLFWcursor* cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);//and GLFW_HAND_CURSOR
	glfwSetCursor(window, cursor);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize game
	SpaceWar.getWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	SpaceWar.Init();
	SpaceWar.State = GAME_ACTIVE;

	// DeltaTime variables
	GLfloat deltaTime = 0.0f;
	GLfloat lastFrame = 0.0f;

	while (!glfwWindowShouldClose(window))
	{
		// Calculate delta time
		double currentFramed = glfwGetTime();
		GLfloat currentFrame = (GLfloat)currentFramed;
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		
		// Update Game state
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		float poscx = (float)xpos;
		float poscy = (float)ypos;
		SpaceWar.Update(deltaTime, poscx, poscy);

		//deltaTime = 0.001f;?
		// Manage user input
		SpaceWar.ProcessInput(deltaTime);

		// Render
		//GLfloat t = sin(currentFrame) / 2 + 0.5;
		//glClearColor(t, 0.12f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		SpaceWar.Render();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	ResourceManager::Clear();
	glfwTerminate();
	return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			SpaceWar.Keys[key] = GL_TRUE;
		else if (action == GLFW_RELEASE)
			SpaceWar.Keys[key] = GL_FALSE;
	}

}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//std::cout << button << "," << std::endl;
	if (button >= 0 && button < 4)
	{
		if (action == GLFW_PRESS)
			SpaceWar.Mouse[button] = GL_TRUE;
		else if(action == GLFW_RELEASE)
			SpaceWar.Mouse[button] = GL_FALSE;
	}
}