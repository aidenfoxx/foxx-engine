#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdio.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

typedef void (*ContextCallback)();

GLFWwindow *contextWindow;

int contextInit(int, int);
void contextDestroy();

int contextWindowOpen(char*, int, int, int, int);
void contextWindowDestroy();

void contextLoopCallback(ContextCallback);
void contextLoop();
void contextLoopStop();

#endif