#ifndef CONTEXT_H
#define CONTEXT_H

#include <stdio.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

typedef void (*ContextError)(int, const char*);
typedef void (*ContextLoop)();

GLFWwindow *contextWindow;

int contextInit(int, int);
void contextDestroy();

int contextWindowOpen(char*, int, int, int, int);
void contextWindowDestroy();

void contextErrorCallback(ContextError);

void contextLoopCallback(ContextLoop);
void contextLoop();
void contextLoopStop();

#endif