#include "Renderer/shader.h"

static int shaderRead(const char*, char**);
static void *shaderGetError(GLuint, GLenum);

Shader *shaderNew(int shaderType, char *shaderData)
{
	Shader *shader;

	if ((shader = malloc(sizeof(Shader))) != NULL)
	{
		shader->shader = glCreateShader(shaderType);
		glShaderSource(shader->shader, 1, (const char**)&shaderData, NULL);
		glCompileShader(shader->shader);
		shader->error = shaderGetError(shader->shader, GL_COMPILE_STATUS);
	}

	return shader;
}

Shader *shaderLoad(int shaderType, const char *shaderPath)
{
	Shader *shader = NULL;
	char *shaderData = NULL;

	if (shaderRead(shaderPath, &shaderData) > 0)
	{
		shader = shaderNew(shaderType, shaderData);
	}

	free(shaderData);

	return shader;
}

void shaderFree(Shader *shader)
{
	if (shader)
	{
		glDeleteShader(shader->shader);
		free(shader->error);
		free(shader);
	}
}

ShaderProgram *shaderProgramNew()
{
	ShaderProgram *program;

	if ((program = malloc(sizeof(ShaderProgram))) != NULL)
	{
		program->error = NULL;
		program->program = glCreateProgram();
	}

	return program;
}

void shaderProgramFree(ShaderProgram *program)
{
	if (program)
	{
		glDeleteProgram(program->program);
		free(program->error);
		free(program);
	}
}

void shaderProgramAttach(ShaderProgram *program, Shader *shader)
{
	glAttachShader(program->program, shader->shader);
}

void shaderProgramDetach(ShaderProgram *program, Shader *shader)
{
	glDetachShader(program->program, shader->shader);
}

int shaderProgramLink(ShaderProgram *program)
{
	glLinkProgram(program->program);
	free(program->error);
	program->error = shaderGetError(program->program, GL_LINK_STATUS);
	return 0;
}

void shaderProgramBind(ShaderProgram *program)
{
	glUseProgram(program->program);
}

void shaderProgramUnbind()
{
	glUseProgram(0);
}

void shaderProgramSetInt(ShaderProgram *program, const char *name, int data)
{
	GLuint location = glGetUniformLocation(program->program, name);
	glUniform1i(location, data);
}

void shaderProgramSetFloat(ShaderProgram *program, const char *name, float data)
{
	GLuint location = glGetUniformLocation(program->program, name);
	glUniform1f(location, data);
}

void shaderProgramSetVec2(ShaderProgram *program, const char *name, Vec2 data)
{
	GLuint location = glGetUniformLocation(program->program, name);
	glUniform2f(location, data.x, data.y);
}

void shaderProgramSetVec3(ShaderProgram *program, const char *name, Vec3 data)
{
	GLuint location = glGetUniformLocation(program->program, name);
	glUniform3f(location, data.x, data.y, data.z);
}

void shaderProgramSetVec4(ShaderProgram *program, const char *name, Vec4 data)
{
	GLuint location = glGetUniformLocation(program->program, name);
	glUniform4f(location, data.x, data.y, data.z, data.w);
}

void shaderProgramSetMat4(ShaderProgram *program, const char *name, Mat4 data)
{
	GLuint location = glGetUniformLocation(program->program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, (float*)&data);
}

char *shaderError(Shader *shader)
{
	return shader->error;
}

char *shaderProgramError(ShaderProgram *program)
{
	return program->error;
}

int shaderRead(const char *shaderPath, char **shaderData)
{
	FILE *shader = fopen(shaderPath, "rb");

	if (!shader)
	{
		return 0;
	}

	fseek(shader, 0, SEEK_END);
	long length = ftell(shader);
	fseek(shader, 0, SEEK_SET);

	*shaderData = calloc(length + 1, 1);

	if (length != fread(*shaderData, 1, length, shader)) 
	{ 
		free(*shaderData);
		return 0;
	}

	fclose(shader);

	return length;
}

void *shaderGetError(GLuint shader, GLenum parameter)
{
	char *returnError = NULL;

	GLint error;
	GLint errorLength = 0;

	glGetShaderiv(shader, parameter, &error);
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &errorLength);

	if (error == GL_FALSE && errorLength > 0)
	{
		returnError = calloc(sizeof(char), errorLength);
		glGetShaderInfoLog(shader, errorLength, NULL, returnError);
	}

	return returnError;
}