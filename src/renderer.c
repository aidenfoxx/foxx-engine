#include "renderer.h"

static void rendererBindVariables(Renderer*, ShaderProgram*, Object*);

static int defaultShaderID;

int rendererInit(Renderer *renderer, Camera *camera)
{
	int returnError = 0;

	Array *shaders = malloc(sizeof(Array));
	arrayInit(shaders);

	Array *objectsVAO = malloc(sizeof(Array));
	arrayInit(objectsVAO);

	Array *objectsStatic = malloc(sizeof(Array));
	arrayInit(objectsStatic);

	Array *objectsDynamic = malloc(sizeof(Array));
	arrayInit(objectsDynamic);

	glGenVertexArrays(1, &renderer->staticVAO);

	renderer->camera = camera;
	renderer->shaders = shaders;
	renderer->objectsVAO = objectsVAO;
	
	renderer->objectsDynamic = objectsDynamic;
	renderer->objectsStatic = objectsStatic;

	/**
	 * Initialize a default scene shader.
	 */
	ShaderProgram *defaultShader = malloc(sizeof(ShaderProgram));
	shaderProgramInit(defaultShader);

	Shader defaultVertex;
	Shader defaultFragment;

	if (shaderInit(&defaultVertex, SHADER_VERTEX, "./assets/shaders/default.vs"))
	{
		shaderDestroy(&defaultVertex);
		return -1;
	}

	
	if (shaderInit(&defaultFragment, SHADER_FRAGMENT, "./assets/shaders/default.fs"))
	{
		shaderDestroy(&defaultVertex);
		shaderDestroy(&defaultFragment);
		return -2;
	}

	shaderAttach(defaultShader, &defaultVertex);
	shaderAttach(defaultShader, &defaultFragment);
	
	if (shaderProgramLink(defaultShader))
	{
		returnError = -3;
	}

	defaultShaderID = rendererAddShader(renderer, defaultShader);
	
	shaderDestroy(&defaultVertex);
	shaderDestroy(&defaultFragment);

	return returnError;
}

/**
 * TODO: Implement better destroy.
 */
void rendererDestroy(Renderer *renderer)
{
	glDeleteVertexArrays(1, &renderer->staticVAO);

	if (defaultShaderID)
	{
		ShaderProgram *shader = arrayGet(renderer->shaders, defaultShaderID - 1);
		shaderProgramDestroy(shader);
	}
	
	for (int i = 0; i < arrayLength(renderer->objectsDynamic); i++)
	{
		Object *objectDynamic = arrayGet(renderer->objectsDynamic, i);

		if (objectDynamic)
		{
			rendererRemoveObject(renderer, i, OBJECT_DYNAMIC);
		}
	}

	glDeleteVertexArrays(1, &renderer->staticVAO);

	arrayDestroy(renderer->shaders);
	arrayDestroy(renderer->objectsVAO);
	arrayDestroy(renderer->objectsDynamic);
	arrayDestroy(renderer->objectsStatic);

	free(renderer->shaders);
	free(renderer->objectsVAO);
	free(renderer->objectsDynamic);
	free(renderer->objectsStatic);
}

int rendererAddShader(Renderer *renderer, ShaderProgram *program)
{
	arrayPush(renderer->shaders, program);
	return arrayLength(renderer->shaders);
}

void rendererRemoveShader(Renderer *renderer, int shaderID)
{
	if (shaderID != defaultShaderID)
	{
		arrayRemove(renderer->shaders, shaderID - 1);
	}
}

int rendererAddObject(Renderer *renderer, Object *object, int objectType)
{
	int objectID;

	switch (objectType)
	{
		case OBJECT_DYNAMIC: ;
			GLuint *vao = malloc(sizeof(GLuint));
			glGenVertexArrays(1, vao);
			glBindVertexArray(*vao);
			arrayPush(renderer->objectsVAO, vao);
			arrayPush(renderer->objectsDynamic, object);
			objectID = arrayLength(renderer->objectsDynamic);
			break;

		case OBJECT_STATIC:
			glBindVertexArray(renderer->staticVAO);
			arrayPush(renderer->objectsStatic, object);
			objectID = arrayLength(renderer->objectsStatic);
			break;

		default:
			return 0;
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

	return objectID;
}

void rendererRemoveObject(Renderer *renderer, int objectID, int objectType)
{
	switch (objectType)
	{
		case OBJECT_DYNAMIC: ;
			GLuint *vao = arrayGet(renderer->objectsVAO, objectID - 1);
			arrayRemove(renderer->objectsDynamic, objectID - 1);
			arrayRemove(renderer->objectsVAO, objectID - 1);
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
			glDrawElements(GL_TRIANGLES, objectStatic->mesh->indicesLength * 3, GL_UNSIGNED_INT, 0);
		}

		for (int i = 0; i < dynamicLength; i++)
		{
			Object *objectDynamic = arrayGet(renderer->objectsDynamic, i);

			if (objectDynamic)
			{
				GLuint* objectVAO = (GLuint*) arrayGet(renderer->objectsVAO, i);

				glBindVertexArray(*objectVAO);

				rendererBindVariables(renderer, shader, objectDynamic);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, objectDynamic->vbo[3]);
				glDrawElements(GL_TRIANGLES, objectDynamic->mesh->indicesLength * 3, GL_UNSIGNED_INT, 0);
			}
		}
	}

	shaderProgramDisable();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void rendererBindVariables(Renderer *renderer, ShaderProgram *shader, Object *object)
{
	Matrix4 model = object->transformMatrix;
	Matrix4 modelView = matrix4MultiplyMatrix4(renderer->camera->view, model);
	Matrix4 modelViewPerspective = matrix4MultiplyMatrix4(renderer->camera->perspective, modelView);

	shaderProgramSetMatrix4(shader, "model", model);
	shaderProgramSetMatrix4(shader, "modelView", modelView);
	shaderProgramSetMatrix4(shader, "modelViewPerspective", modelViewPerspective);
	shaderProgramSetMatrix4(shader, "normalMatrix", matrix4Transpose(matrix4Invert(modelView)));
}