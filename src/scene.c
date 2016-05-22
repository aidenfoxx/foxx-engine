#include "scene.h"

static int defaultShaderID;

int sceneInit(Scene *scene, Camera *camera)
{
	Array *shaders = malloc(sizeof(Array));
	arrayInit(shaders);

	Array *actors = malloc(sizeof(Array));
	arrayInit(actors);

	Array *props = malloc(sizeof(Array));
	arrayInit(props);

	glGenVertexArrays(1, &scene->vao);

	scene->shaders = shaders;
	scene->camera = camera;
	scene->actors = actors;
	scene->props = props;

	/**
	 * Initialize a default scene shader.
	 */
	ShaderProgram *defaultShader = malloc(sizeof(ShaderProgram));
	shaderProgramInit(defaultShader);

	Shader defaultVertex;
	Shader defaultFragment;

	if (shaderInit(&defaultVertex, SHADER_VERTEX, "./assets/shaders/default.vs"))
	{
		return -1;
	}

	if (shaderInit(&defaultFragment, SHADER_FRAGMENT, "./assets/shaders/default.fs"))
	{
		return -2;
	}

	shaderAttach(defaultShader, &defaultVertex);
	shaderAttach(defaultShader, &defaultFragment);

	if (shaderProgramLink(defaultShader))
	{
		return -3;
	}

	defaultShaderID = sceneAddShader(scene, defaultShader);

	shaderDestroy(&defaultVertex);
	shaderDestroy(&defaultFragment);

	return 0;
}

void sceneDestroy(Scene *scene)
{
	glDeleteVertexArrays(1, &scene->vao);

	if (defaultShaderID)
	{
		ShaderProgram *shader = arrayGet(scene->shaders, defaultShaderID - 1);
		shaderProgramDestroy(shader);
	}
	
	free(scene->shaders);
	free(scene->actors);
	free(scene->props);
}

int sceneAddShader(Scene *scene, ShaderProgram *program)
{
	arrayPush(scene->shaders, program);
	return arrayLength(scene->shaders);
}

void sceneRemoveShader(Scene *scene, int shaderID)
{
	if (shaderID != defaultShaderID)
	{
		arrayRemove(scene->shaders, shaderID - 1);
	}
}

void sceneAddProp(Scene *scene, Prop *prop)
{
	arrayPush(scene->props, prop);

	glBindVertexArray(scene->vao);

	glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[1]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[2]);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

int sceneAddActor(Scene *scene, Actor *actor)
{
	arrayPush(scene->actors, actor);
	return arrayLength(scene->actors);
}

void sceneRemoveActor(Scene *scene, int actorID)
{
	arrayRemove(scene->actors, actorID - 1);
}

void sceneRender(Scene *scene)
{
	int shaderLength = arrayLength(scene->shaders);

	for (int i = 0; i < shaderLength; i++)
	{
		ShaderProgram *shader = arrayGet(scene->shaders, i);

		if (!shader)
		{
			continue;
		}

		shaderProgramEnable(shader);

		int propLength = arrayLength(scene->props);
		int actorLength = arrayLength(scene->actors);

		shaderProgramSetMatrix4(shader, "viewMatrix", scene->camera->view);
		shaderProgramSetMatrix4(shader, "perspectiveMatrix", scene->camera->perspective);
		
		glBindVertexArray(scene->vao);

		for (int i = 0; i < propLength; i++)
		{
			Prop *prop = arrayGet(scene->props, i);

			shaderProgramSetMatrix4(shader, "modelMatrix", prop->matrix);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prop->vbo[3]);
			glDrawElements(GL_TRIANGLES, prop->asset->indicesLength * 3, GL_UNSIGNED_INT, 0);
		}

		for (int i = 0; i < actorLength; i++)
		{
			Actor *actor = arrayGet(scene->actors, i);

			shaderProgramSetMatrix4(shader, "modelMatrix", actor->prop->matrix);

			glBindVertexArray(actor->vao);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, actor->prop->vbo[3]);
			glDrawElements(GL_TRIANGLES, actor->prop->asset->indicesLength * 3, GL_UNSIGNED_INT, 0);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
}