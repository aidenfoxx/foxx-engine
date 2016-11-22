#include "Renderer/shader.h"

static int shaderRead(const char*, char**);

Shader *shaderNew(const char *shaderPath, int shaderType)
{
	Shader *shader = NULL;
	char *shaderData = NULL;

	if ((shader = malloc(sizeof(Shader))) != NULL)
	{
		shader->error = NULL;
		shader->shaderID = glCreateShader(shaderType);

		if (shaderRead(shaderPath, &shaderData) > 0)
		{
			glShaderSource(shader->shaderID, 1, (const char**)&shaderData, NULL);
			glCompileShader(shader->shaderID);

			GLint errorStatus;
			glGetShaderiv(shader->shaderID, GL_COMPILE_STATUS, &errorStatus);

			if (errorStatus == GL_FALSE)
			{
				GLint errorLength;
				glGetShaderiv(shader->shaderID, GL_INFO_LOG_LENGTH, &errorLength);

				/**
				 * Use +2 so we can add a newline character
				 * at the begining.
				 */
				shader->error = malloc((errorLength * sizeof(char)) + 1);
				glGetShaderInfoLog(shader->shaderID, errorLength, NULL, shader->error);
				memmove(&shader->error[1], &shader->error[0], errorLength);
				shader->error[0] = '\n';
			}
		}

		free(shaderData);
	}

	return shader;
}

void shaderFree(Shader *shader)
{
	if (shader != NULL)
	{
		glDeleteShader(shader->shaderID);
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
		program->programID = glCreateProgram();
	}

	return program;
}

void shaderProgramFree(ShaderProgram *program)
{
	glDeleteProgram(program->programID);
	free(program->error);
	free(program);
}

void shaderProgramAttach(ShaderProgram *program, Shader *shader)
{
	glAttachShader(program->programID, shader->shaderID);
}

void shaderProgramDetach(ShaderProgram *program, Shader *shader)
{
	glDetachShader(program->programID, shader->shaderID);
}

int shaderProgramLink(ShaderProgram *program)
{
	glLinkProgram(program->programID);

	GLint errorStatus;
	glGetProgramiv(program->programID, GL_LINK_STATUS, &errorStatus);

	if (errorStatus == GL_FALSE)
	{
		GLint errorLength;
		glGetProgramiv(program->programID, GL_INFO_LOG_LENGTH, &errorLength);

		program->error = realloc(program->error, (errorLength * sizeof(char)) + 2);
		glGetProgramInfoLog(program->programID, errorLength, NULL, program->error);
		memmove(&program->error[1], &program->error[0], errorLength);
		program->error[0] = '\n';

		return -1;
	}

	return 0;
}

void shaderProgramEnable(ShaderProgram *program)
{
	glUseProgram(program->programID);
}

void shaderProgramDisable()
{
	glUseProgram(0);
}

void shaderProgramSetInt(ShaderProgram *program, const char *name, int data)
{
	GLuint location = glGetUniformLocation(program->programID, name);
	glUniform1i(location, data);
}

void shaderProgramSetFloat(ShaderProgram *program, const char *name, float data)
{
	GLuint location = glGetUniformLocation(program->programID, name);
	glUniform1f(location, data);
}

void shaderProgramSetVec2(ShaderProgram *program, const char *name, Vec2 data)
{
	GLuint location = glGetUniformLocation(program->programID, name);
	glUniform2f(location, data.x, data.y);
}

void shaderProgramSetVec3(ShaderProgram *program, const char *name, Vec3 data)
{
	GLuint location = glGetUniformLocation(program->programID, name);
	glUniform3f(location, data.x, data.y, data.z);
}

void shaderProgramSetVec4(ShaderProgram *program, const char *name, Vec4 data)
{
	GLuint location = glGetUniformLocation(program->programID, name);
	glUniform4f(location, data.x, data.y, data.z, data.w);
}

void shaderProgramSetMat4(ShaderProgram *program, const char *name, Mat4 data)
{
	GLuint location = glGetUniformLocation(program->programID, name);
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
