#include "shader.h"

static int shaderRead(const char*, char**);

int shaderInit(Shader *shader, int shaderType, const char *shaderPath)
{
	char *shaderData;

	if (shaderRead(shaderPath, &shaderData))
	{
		return -1;
	}

	shader->error = NULL;
	shader->shader = glCreateShader(shaderType);
	
	glShaderSource(shader->shader, 1, (const char**) &shaderData, NULL);
	glCompileShader(shader->shader);
	free(shaderData);

	GLint errorStatus;
	glGetShaderiv(shader->shader, GL_COMPILE_STATUS, &errorStatus);

	if (errorStatus == GL_FALSE)
	{
		GLint errorLength;
		glGetShaderiv(shader->shader, GL_INFO_LOG_LENGTH, &errorLength);

		shader->error = realloc(shader->error, sizeof(char) * errorLength + 1);
		glGetShaderInfoLog(shader->shader, errorLength, NULL, shader->error);

		return -2;
	}

	return 0;
}

void shaderDestroy(Shader *shader)
{
	glDeleteShader(shader->shader);
	free(shader->error);
}

void shaderAttach(ShaderProgram *program, Shader *shader)
{
	glAttachShader(program->program, shader->shader);
}

void shaderDetach(ShaderProgram *program, Shader *shader)
{
	glDetachShader(program->program, shader->shader);
}

void shaderProgramInit(ShaderProgram *program)
{
	program->error = malloc(0);
	program->program = glCreateProgram();
}

void shaderProgramDestroy(ShaderProgram *program)
{
	glDeleteProgram(program->program);
	free(program->error);
}

int shaderProgramLink(ShaderProgram *program)
{
	glLinkProgram(program->program);

	GLint errorStatus;
	glGetProgramiv(program->program, GL_LINK_STATUS, &errorStatus);

	if (errorStatus == GL_FALSE)
	{
		GLint errorLength;
		glGetProgramiv(program->program, GL_INFO_LOG_LENGTH, &errorLength);

		program->error = realloc(program->error, sizeof(char) * errorLength + 1);
		glGetProgramInfoLog(program->program, errorLength, NULL, program->error);

		return -1;
	}

	return 0;
}


void shaderProgramEnable(ShaderProgram *program)
{
	glUseProgram(program->program);
}

void shaderProgramDisable()
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

void shaderProgramSetMatrix(ShaderProgram *program, const char *name, Matrix data)
{
	GLuint location = glGetUniformLocation(program->program, name);
	glUniformMatrix4fv(location, 1, GL_FALSE, (float*) &data);
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
		return -1;
	}

	fseek(shader, 0, SEEK_END);
	long length = ftell(shader);
	fseek(shader, 0, SEEK_SET);

	*shaderData = calloc(length + 1, sizeof(char));

	if (length != fread(*shaderData, sizeof(char), length, shader)) 
	{ 
		free(*shaderData);
		return -2;
	}

	fclose(shader);

	return 0;
}
