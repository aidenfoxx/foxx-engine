#include "renderer.h"

Renderer *rendererNew(Camera *camera)
{
	Renderer *renderer;

	if ((renderer = malloc(sizeof(Renderer))) != NULL)
	{
		renderer->shaders = arrayNew();
		renderer->objects = arrayNew();
		renderer->objectsVAO = arrayNew();
		renderer->camera = camera;
	}

	return renderer;
}

void rendererFree(Renderer *renderer)
{
	if (renderer)
	{
		int objectsLength = arrayLength(renderer->objects);

		for (int i = 0; i < objectsLength; i++)
		{
			rendererRemoveObject(renderer, i);
		}	

		arrayFree(renderer->shaders);
		arrayFree(renderer->objects);
		arrayFree(renderer->objectsVAO);
		free(renderer);
	}
}

int rendererAddShader(Renderer *renderer, ShaderProgram *program)
{
	arrayPush(renderer->shaders, program);
	return arrayLength(renderer->shaders);
}

int rendererAddObject(Renderer *renderer, Object *object)
{
	GLuint *vao = NULL;
	ModelBuffer *modelBuffer;
	
	if ((vao = malloc(sizeof(GLuint))) != NULL && (modelBuffer = objectGetModelBuffer(object)))
	{
		glGenVertexArrays(1, vao);
		glBindVertexArray(*vao);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		modelBufferBind(modelBuffer, MODEL_VERTICES);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		modelBufferBind(modelBuffer, MODEL_UVS);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		modelBufferBind(modelBuffer, MODEL_NORMALS);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

		modelBufferUnbind();
		glBindVertexArray(0);

		arrayPush(renderer->objects, object);
		arrayPush(renderer->objectsVAO, vao);

		return arrayLength(renderer->objects);
	}

	free(vao);

	return -1;
}


void rendererRemoveShader(Renderer *renderer, int shaderID)
{
	arrayRemove(renderer->shaders, shaderID - 1);
}

void rendererRemoveObject(Renderer *renderer, int objectID)
{
	GLuint *vao;

	if ((vao = (GLuint*)arrayGet(renderer->objectsVAO, objectID - 1)) != NULL)
	{
		glDeleteVertexArrays(1, vao);
		arrayRemove(renderer->objectsVAO, objectID - 1);
		arrayRemove(renderer->objects, objectID - 1);
		free(vao);
	}
}

void rendererStep(Renderer *renderer)
{
	int shaderLength = arrayLength(renderer->shaders);
	int objectsLength = arrayLength(renderer->objects);

	for (int i = 0; i < shaderLength; i++)
	{
		ShaderProgram *program;

		if ((program = (ShaderProgram*)arrayGet(renderer->shaders, i)) == NULL)
		{
			continue;
		}

		shaderProgramBind(program);

		for (int i = 0; i < objectsLength; i++)
		{
			Object *object;
			ModelBuffer *modelBuffer;

			if ((object = (Object*)arrayGet(renderer->objects, i)) != NULL && (modelBuffer = objectGetModelBuffer(object)))
			{
				Mat4 M = objectGetTransform(object);
				Mat4 MV = mat4MultiplyMat4(cameraGetView(renderer->camera), M);
				Mat4 MVP = mat4MultiplyMat4(cameraGetProjection(renderer->camera), MV);

				shaderProgramSetMat4(program, "model", M);
				shaderProgramSetMat4(program, "modelView", MV);
				shaderProgramSetMat4(program, "modelViewProjection", MVP);
				shaderProgramSetMat4(program, "normalMatrix", mat4Transpose(mat4Inverse(MV)));

				TextureBuffer *diffuse;
				TextureBuffer *specular;
				TextureBuffer *normal;

				if (diffuse = objectGetTextureBuffer(object, TEXTURE_DIFFUSE))
				{
					glActiveTexture(GL_TEXTURE0);
					textureBufferBind(diffuse);
				}
				
				if (specular = objectGetTextureBuffer(object, TEXTURE_SPECULAR))
				{
					glActiveTexture(GL_TEXTURE1);
					textureBufferBind(specular);
				}

				if (normal = objectGetTextureBuffer(object, TEXTURE_NORMAL))
				{
					glActiveTexture(GL_TEXTURE2);
					textureBufferBind(normal);
				}

				GLuint *vao = (GLuint*)arrayGet(renderer->objectsVAO, i);

				glBindVertexArray(*vao);
				modelBufferBind(modelBuffer, MODEL_INDICES);
				glDrawElements(GL_TRIANGLES, modelBufferGetModel(modelBuffer)->indicesLength * 3, GL_UNSIGNED_INT, 0);
			}
		}
	}

	glActiveTexture(GL_TEXTURE0);
	modelBufferUnbind();

	glActiveTexture(GL_TEXTURE1);
	modelBufferUnbind();

	glActiveTexture(GL_TEXTURE2);
	modelBufferUnbind();

	textureBufferUnbind();
	shaderProgramUnbind();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}