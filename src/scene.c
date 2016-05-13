#include "scene.h"

void sceneInit(Scene *scene, Camera *camera, ShaderProgram *shader)
{
	Array *actors = malloc(sizeof(Array));
	arrayInit(actors);

	Array *props = malloc(sizeof(Array));
	arrayInit(props);

	glGenVertexArrays(1, &scene->vao);

	scene->camera = camera;
	scene->shader = shader;
	scene->actors = actors;
	scene->props = props;
}

void sceneDestroy(Scene *scene)
{
	glDeleteVertexArrays(1, &scene->vao);
	free(scene->actors);
}

void sceneAddProp(Scene *scene, Prop *prop)
{
	arrayPush(scene->props, prop);

	/**
	 * Bind the VAO.
	 */
	glBindVertexArray(scene->vao);

	/**
	 * Load the buffers and bind to the VAO.
	 */
	glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[0]);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[1]);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, prop->vbo[2]);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, prop->ibo);
	
	/**
	 * Unbind buffers.
	 */
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
	int propLength = arrayLength(scene->props);
	int actorLength = arrayLength(scene->actors);

	shaderProgramEnable(scene->shader);

	shaderProgramSetMatrix(scene->shader, "viewMatrix", scene->camera->view);
	shaderProgramSetMatrix(scene->shader, "perspectiveMatrix", scene->camera->perspective);

	shaderProgramSetVec3(scene->shader, "lightPosition", vec3New(4.0f, 4.0f, 4.0f));
	shaderProgramSetVec3(scene->shader, "cameraPosition", scene->camera->translation);
	
	glBindVertexArray(scene->vao);

	for (int i = 0; i < propLength; i++)
	{
		Prop *prop = arrayGet(scene->props, i);

		shaderProgramSetMatrix(scene->shader, "modelMatrix", prop->matrix);
		
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, prop->ibo);
		glDrawElements(GL_TRIANGLES, prop->asset->indexLength * 3, GL_UNSIGNED_INT, 0);
	}

	for (int i = 0; i < actorLength; i++)
	{
		Actor *actor = arrayGet(scene->actors, i);

		shaderProgramSetMatrix(scene->shader, "modelMatrix", actor->prop->matrix);

		glBindVertexArray(actor->vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, actor->prop->ibo);
		glDrawElements(GL_TRIANGLES, actor->prop->asset->indexLength * 3, GL_UNSIGNED_INT, 0);
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}