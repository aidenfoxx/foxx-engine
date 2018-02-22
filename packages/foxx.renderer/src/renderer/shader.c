#include "renderer/shader.h"

static ShaderStatus shaderCompileError(GLuint, char**);
static ShaderStatus shaderLinkError(GLuint, char**);

Shader *shaderNew(const char *vertexData, const char *fragmentData)
{
	Shader *shader = malloc(sizeof(Shader));

	shader->program = glCreateProgram();
	shader->error = NULL;

	GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(vertex, 1, (const GLchar**)&vertexData, NULL);
	glShaderSource(fragment , 1, (const GLchar**)&fragmentData, NULL);

	glCompileShader(vertex);
	glCompileShader(fragment);

	if (shaderCompileError(vertex, &shader->error) == SHADER_SUCCESS && 
		shaderCompileError(fragment, &shader->error) == SHADER_SUCCESS) {
		glAttachShader(shader->program, vertex);
		glAttachShader(shader->program, fragment);

		glLinkProgram(shader->program);

		shaderLinkError(shader->program, &shader->error);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return shader;
}

void shaderFree(Shader *shader)
{
	assert(shader != NULL);
	glDeleteProgram(shader->program);
	if (shader->error != NULL) {
		free(shader->error);
	}
	free(shader);
}

const char *shaderError(Shader *shader)
{
	assert(shader != NULL);
	return (const char*)shader->error;
}

ShaderStatus shaderCompileError(GLuint buffer, char **error)
{
	GLint success;

	glGetShaderiv(buffer, GL_COMPILE_STATUS, &success);

	if (success != GL_TRUE) {
		/**
		 * Generate a buffer for the error message
		 * and return.
		 */
		GLuint length;
		glGetShaderiv(buffer, GL_INFO_LOG_LENGTH, &length);

		*error = calloc(length, sizeof(char));
		glGetShaderInfoLog(buffer, length, NULL, *error);

		return SHADER_ERROR;	
	}

	return SHADER_SUCCESS;
}

ShaderStatus shaderLinkError(GLuint buffer, char **error)
{
	GLint success;

	glGetProgramiv(buffer, GL_LINK_STATUS, &success);

	if (success != GL_TRUE) {
		/**
		 * Generate a buffer for the error message
		 * and return.
		 */
		GLuint length;
		glGetProgramiv(buffer, GL_INFO_LOG_LENGTH, &length);

		*error = calloc(length, sizeof(char));
		glGetShaderInfoLog(buffer, length, NULL, *error);

		return SHADER_ERROR;
	}

	return SHADER_SUCCESS;
}