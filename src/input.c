#include "input.h"

void inputSetKeyCallback(Window *window, KeyCallback callback)
{
	glfwSetKeyCallback(*window, callback);
}