#include "Scene/actor.h"

void actorInit(Actor *actor, Asset *asset)
{
	actor->prop = malloc(sizeof(Prop));
	propInit(actor->prop, asset);

	/**
	 * Bind the VAO.
	 */
	glGenVertexArrays(1, &actor->vao);
	glBindVertexArray(actor->vao);

	/**
	 * Load the buffers and bind to the VAO.
	 */
    glBindBuffer(GL_ARRAY_BUFFER, actor->prop->vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, actor->prop->vbo[1]);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, actor->prop->vbo[2]);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, actor->prop->vbo[3]);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);

	/**
	 * Unbind buffers.
	 */
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void actorDestroy(Actor *actor)
{
	glDeleteVertexArrays(1, &actor->vao);
	propDestroy(actor->prop);
	free(actor->prop);
}

void actorRotate(Actor *actor, float x, float y, float z)
{
	propRotate(actor->prop, x, y, z);
}

void actorTranslate(Actor *actor, float x, float y, float z)
{
	propTranslate(actor->prop, x, y, z);
}

void actorScale(Actor *actor, float x, float y, float z)
{
	propScale(actor->prop, x, y, z);
}