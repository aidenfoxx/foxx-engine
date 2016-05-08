#include "context.h"

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
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    return 0;
}

void contextDestroy()
{
    glfwTerminate();
}

int contextWindowOpen(Window *window, char* title, int width, int height, int fullscreen, int vsync)
{
	*window = glfwCreateWindow(width, height, title, fullscreen ? glfwGetPrimaryMonitor() : NULL, NULL);

    if (!*window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(*window);
    glfwSwapInterval(vsync);

    if (gl3wInit())
    {
        return -2;
    }

    if (!gl3wIsSupported(glMajor, glMinor))
    {
        return -3;
    }

    return 0;
}

int contextWindowShouldClose(Window *window)
{
	return glfwWindowShouldClose(*window);
}

void contextWindowDestroy(Window *window)
{
	glfwDestroyWindow(*window);
}

void contextWindowTick(Window *window)
{
	glfwSwapBuffers(*window);
	glfwPollEvents();
}