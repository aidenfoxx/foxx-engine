#ifndef SHADER_H
#define SHADER_H

#define SHADER_VERTEX GL_VERTEX_SHADER
#define SHADER_FRAGMENT GL_FRAGMENT_SHADER

#include <stdio.h>
#include <stdlib.h>

#include "context.h"
#include "glmath.h"

typedef struct {
	char *error;
	GLuint shaderID;
} Shader;

typedef struct {
	char *error;
	GLuint programID;
} ShaderProgram;

void shaderProgramInit(ShaderProgram*);
void shaderProgramDestroy(ShaderProgram*);
int shaderProgramLink(ShaderProgram*);
void shaderProgramEnable(ShaderProgram*);
void shaderProgramDisable();
void shaderProgramSetInt(ShaderProgram*, const char*, int);
void shaderProgramSetFloat(ShaderProgram*, const char*, float);
void shaderProgramSetVector2f(ShaderProgram*, const char*, Vector2f);
void shaderProgramSetVector3f(ShaderProgram*, const char*, Vector3f);
void shaderProgramSetVector4f(ShaderProgram*, const char*, Vector4f);
void shaderProgramSetMatrix4(ShaderProgram*, const char*, Matrix4);

int shaderInit(Shader*, int, const char*);
void shaderDestroy(Shader*);
void shaderAttach(ShaderProgram*, Shader*);
void shaderDetach(ShaderProgram*, Shader*);

char *shaderError(Shader*);
char *shaderProgramError(ShaderProgram*);

#endif