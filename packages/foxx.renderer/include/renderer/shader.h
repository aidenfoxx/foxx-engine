#ifndef RENDERER_SHADER_H
#define RENDERER_SHADER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <gl/gl3w.h>

typedef enum {
	SHADER_SUCCESS = 0,
	SHADER_ERROR = INT_MIN
} ShaderStatus;

typedef struct {
	GLuint program;
	char *error;
} Shader;

Shader *shaderNew(const char*, const char*);
void shaderFree(Shader*);

const char *shaderError(Shader*);

#endif