#ifndef RENDERER_SHADER_H
#define RENDERER_SHADER_H

#define SHADER_VERTEX GL_VERTEX_SHADER
#define SHADER_FRAGMENT GL_FRAGMENT_SHADER

#include <stdio.h>
#include <stdlib.h>

#include "context.h"
#include "Tools/glmath.h"

typedef struct {
	char *error;
	GLuint shaderID;
} Shader;

typedef struct {
	char *error;
	GLuint programID;
} ShaderProgram;

Shader *shaderNew(int, const char*);
void shaderFree(Shader*);

ShaderProgram *shaderProgramNew();
void shaderProgramFree(ShaderProgram*);

void shaderProgramAttach(ShaderProgram*, Shader*);
void shaderProgramDetach(ShaderProgram*, Shader*);

int shaderProgramLink(ShaderProgram*);

void shaderProgramEnable(ShaderProgram*);
void shaderProgramDisable();

void shaderProgramSetInt(ShaderProgram*, const char*, int);
void shaderProgramSetFloat(ShaderProgram*, const char*, float);
void shaderProgramSetVec2(ShaderProgram*, const char*, Vec2);
void shaderProgramSetVec3(ShaderProgram*, const char*, Vec3);
void shaderProgramSetVec4(ShaderProgram*, const char*, Vec4);
void shaderProgramSetMat4(ShaderProgram*, const char*, Mat4);

char *shaderError(Shader*);
char *shaderProgramError(ShaderProgram*);

#endif