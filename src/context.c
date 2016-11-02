#include "context.h"

static ContextError errorCallback;
static ContextLoop loopCallback;

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
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_ANY_PROFILE);

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

	if (gl3wInit() || !gl3wIsSupported(glMajor, glMinor))
	{
		glfwTerminate();
		return -2;
	}

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	return 0;
}

void contextWindowDestroy()
{
	glfwDestroyWindow(contextWindow);
	contextWindow = NULL;
}

void contextErrorCallback(ContextError callback)
{
	errorCallback = callback;
	glfwSetErrorCallback(errorCallback);
}

void contextLoopCallback(ContextLoop callback)
{
	loopCallback = callback;
}

void contextLoop()
{
	if (contextWindow && loopCallback)
	{
		glfwSetWindowShouldClose(contextWindow, 0);

		while(contextWindow && !glfwWindowShouldClose(contextWindow))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			loopCallback();

			glfwSwapBuffers(contextWindow);
			glfwPollEvents();
		}       
	}
}

void contextLoopStop()
{
	glfwSetWindowShouldClose(contextWindow, 1);
}