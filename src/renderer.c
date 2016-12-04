#include "renderer.h"

static void rendererBindVariables(Renderer*, ShaderProgram*, Object*);

Renderer *rendererNew(Camera *camera)
{
	Renderer *renderer;

	if ((renderer = malloc(sizeof(Renderer))) != NULL)
	{
		renderer->shaders = arrayNew();
		renderer->dynamicVAOs = arrayNew();
		renderer->objectsStatic = arrayNew();
		renderer->objectsDynamic = arrayNew();
		renderer->shaders = arrayNew();
		renderer->camera = camera;

		glGenVertexArrays(1, &renderer->staticVAO);
	}

	return renderer;
}

void rendererFree(Renderer *renderer)
{
	if (renderer)
	{
		glDeleteVertexArrays(1, &renderer->staticVAO);
		arrayFree(renderer->objectsDynamic);
		arrayFree(renderer->objectsStatic);
		arrayFree(renderer->dynamicVAOs);
		arrayFree(renderer->shaders);
		free(renderer);
	}
}

int rendererAddShader(Renderer *renderer, ShaderProgram *program)
{
	arrayPush(renderer->shaders, program);
	return arrayLength(renderer->shaders);
}

void rendererRemoveShader(Renderer *renderer, int shaderID)
{
	arrayRemove(renderer->shaders, shaderID - 1);
}

int rendererAddObject(int objectType, Renderer *renderer, Object *object)
{
	int objectID = 0;

	if (object)
	{
		switch (objectType)
		{
			/**
			 * Dynamic objects get their own VAO.
			 */
			case OBJECT_DYNAMIC: ;
				GLuint *vao = malloc(sizeof(GLuint));
				glGenVertexArrays(1, vao);
				glBindVertexArray(*vao);
				arrayPush(renderer->dynamicVAOs, vao);
				arrayPush(renderer->objectsDynamic, object);
				objectID = arrayLength(renderer->objectsDynamic);
				break;

			/**
			 * Static objects are added to a global VAO.
			 */
			case OBJECT_STATIC:
				glBindVertexArray(renderer->staticVAO);
				arrayPush(renderer->objectsStatic, object);
				objectID = arrayLength(renderer->objectsStatic);
				break;
		}

		glBindBuffer(GL_ARRAY_BUFFER, object->vbo[0]);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, object->vbo[1]);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		glBindBuffer(GL_ARRAY_BUFFER, object->vbo[2]);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	
	return objectID;
}

void rendererRemoveObject(int objectType, Renderer *renderer, int objectID)
{
	switch (objectType)
	{
		case OBJECT_DYNAMIC: ;
			GLuint *vao = arrayGet(renderer->dynamicVAOs, objectID - 1);
			arrayRemove(renderer->objectsDynamic, objectID - 1);
			arrayRemove(renderer->dynamicVAOs, objectID - 1);
			glDeleteVertexArrays(1, vao);
			free(vao);
			break;
	}
}

void rendererExecute(Renderer *renderer)
{
	ShaderProgram *shader;
	int shaderLength = arrayLength(renderer->shaders);
	int staticLength = arrayLength(renderer->objectsStatic);
	int dynamicLength = arrayLength(renderer->objectsDynamic);

	glBindVertexArray(renderer->staticVAO);

	for (int i = 0; i < shaderLength; i++)
	{
		if (!(shader = arrayGet(renderer->shaders, i)))
		{
			continue;
		}

		shaderProgramEnable(shader);

		for (int i = 0; i < staticLength; i++)
		{
			Object *objectStatic = arrayGet(renderer->objectsStatic, i);

			rendererBindVariables(renderer, shader, objectStatic);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectStatic->vbo[3]);
			glBindTexture(GL_TEXTURE_2D, objectStatic->diffuse);
			glDrawElements(GL_TRIANGLES, objectStatic->indicesLength * 3, GL_UNSIGNED_INT, 0);
		}

		for (int i = 0; i < dynamicLength; i++)
		{
			Object *objectDynamic = arrayGet(renderer->objectsDynamic, i);

			if (objectDynamic)
			{
				GLuint* objectVAO = (GLuint*)arrayGet(renderer->dynamicVAOs, i);

				rendererBindVariables(renderer, shader, objectDynamic);
				glBindVertexArray(*objectVAO);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectDynamic->vbo[3]);
				glBindTexture(GL_TEXTURE_2D, objectDynamic->diffuse);
				glDrawElements(GL_TRIANGLES, objectDynamic->indicesLength * 3, GL_UNSIGNED_INT, 0);
			}
		}
	}

	shaderProgramDisable();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void rendererBindVariables(Renderer *renderer, ShaderProgram *shader, Object *object)
{
	Mat4 model = object->transformMatrix;
	Mat4 modelView = mat4MultiplyMat4(cameraGetView(renderer->camera), model);
	Mat4 modelViewPerspective = mat4MultiplyMat4(cameraGetProjection(renderer->camera), modelView);

	shaderProgramSetMat4(shader, "model", model);
	shaderProgramSetMat4(shader, "modelView", modelView);
	shaderProgramSetMat4(shader, "modelViewPerspective", modelViewPerspective);
	shaderProgramSetMat4(shader, "normalMatrix", mat4Transpose(mat4Inverse(modelView)));
}