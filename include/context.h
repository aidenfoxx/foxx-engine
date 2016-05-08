#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdio.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

typedef GLFWwindow* Window;

int contextInit(int, int);
void contextDestroy();

int contextWindowOpen(Window*, char*, int, int, int, int);
int contextWindowShouldClose(Window*);
void contextWindowDestroy(Window*);
void contextWindowTick(Window*);

#endif