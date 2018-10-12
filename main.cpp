#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>
#include "game.h"
#include "resource_manage.h"


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

const GLuint SCREEN_WIDTH = 1600;
const GLuint SCREEN_HEIGHT = 900;
Game SpaceWar(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char *argv[])
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "SpaceWarV2", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	//glGetError(); 
	glfwSetKeyCallback(window, key_callback);
	//glfwSetFramebufferSizeCallback(window, key_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	//glViewport(0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2);
	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// Initialize game
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
		
		//deltaTime = 0.001f;
		// Manage user input
		SpaceWar.ProcessInput(deltaTime);

		// Update Game state
		SpaceWar.Update(deltaTime);

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

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
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