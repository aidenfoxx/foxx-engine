#include "context.h"

static ContextCallback contextCallback;

static int glMajor;
static int glMinor;

int contextInit(int major, int minor)
{
	if (!glfwInit())
	{
		return -1;
	}

	glMajor = major;
	glMinor = minor;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	return 0;
}

void contextDestroy()
{
	contextWindowDestroy();
	glfwTerminate();
}

int contextWindowOpen(char* title, int width, int height, int fullscreen, int vsync)
{
	contextWindow = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

	if (!contextWindow)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(contextWindow);
	glfwSwapInterval(vsync);

	if (gl3wInit())
	{
		return -2;
	}

	if (!gl3wIsSupported(glMajor, glMinor))
	{
		return -3;
	}

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	return 0;
}

void contextWindowDestroy()
{
	glfwDestroyWindow(contextWindow);
	contextWindow = NULL;
}

void contextLoopCallback(ContextCallback callback)
{
	contextCallback = callback;
}

void contextLoop()
{
	if (contextWindow && contextCallback)
	{
		glfwSetWindowShouldClose(contextWindow, 0);

		/**
		 * TODO: Figure out why SwapBuffer is disabling
		 * depth test.
		 */
		while(contextWindow && !glfwWindowShouldClose(contextWindow))
		{
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			printf("%i\n", glIsEnabled(GL_DEPTH_TEST));

			contextCallback();

			glfwSwapBuffers(contextWindow);
			glfwPollEvents();
		}       
	}
}

void contextLoopStop()
{
	glfwSetWindowShouldClose(contextWindow, 1);
}