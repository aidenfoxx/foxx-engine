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
	GLuint shader;
} Shader;

typedef struct {
	char *error;
	GLuint program;
} ShaderProgram;

int shaderInit(Shader*, int, const char*);
void shaderDestroy(Shader*);
void shaderAttach(ShaderProgram*, Shader*);
void shaderDetach(ShaderProgram*, Shader*);

void shaderProgramInit(ShaderProgram*);
void shaderProgramDestroy(ShaderProgram*);
int shaderProgramLink(ShaderProgram*);

void shaderProgramEnable(ShaderProgram*);
void shaderProgramDisable();

void shaderProgramSetInt(ShaderProgram*, const char*, int);
void shaderProgramSetFloat(ShaderProgram*, const char*, float);
void shaderProgramSetVec2(ShaderProgram*, const char*, Vec2);
void shaderProgramSetVec3(ShaderProgram*, const char*, Vec3);
void shaderProgramSetVec4(ShaderProgram*, const char*, Vec4);
void shaderProgramSetMatrix(ShaderProgram*, const char*, Matrix);

char *shaderError(Shader*);
char *shaderProgramError(ShaderProgram*);


#endif