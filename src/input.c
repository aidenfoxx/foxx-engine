#include "input.h"
#include "context.h"

static ButtonCallback buttonCallback;

static void inputKeyCallbackWrapper(GLFWwindow*, int, int, int, int);
static void inputMouseCallbackWrapper(GLFWwindow*, int, int, int);

void inputButtonCallback(ButtonCallback callback)
{
	buttonCallback = callback;
	glfwSetKeyCallback(contextWindow, inputKeyCallbackWrapper);
	glfwSetMouseButtonCallback(contextWindow, inputMouseCallbackWrapper);
}

void inputKeyCallbackWrapper(GLFWwindow* window, int button, int scancode, int action, int mods)
{
	if (buttonCallback)
	{
		buttonCallback(button, action);
	}
}

void inputMouseCallbackWrapper(GLFWwindow* window, int button, int action, int mods)
{
	if (buttonCallback)
	{
		buttonCallback(button, action);
	}
}