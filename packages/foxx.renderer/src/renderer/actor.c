#include "renderer/actor.h"

Actor *actorNew(Scene *scene)
{
	assert(scene != NULL);

	Actor *actor = malloc(sizeof(Actor));

	actor->parent = (void**)&scene->actors.data[scene->actors.length];
	actor->renderables.data = malloc(128 * sizeof(Renderable*));
	actor->renderables.length = 0;
	actor->translation = vec3(0.0f, 0.0f, 0.0f);
	actor->rotation = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	actor->scale = vec3(1.0f, 1.0f, 1.0f);
	actor->transform = mat4MultiplyMat4(
		mat4Translation(actor->translation),
		mat4MultiplyMat4(
			mat4RotationQuat(actor->rotation),
			mat4Scale(actor->scale)	
		)
	);

	scene->actors.data[scene->actors.length] = actor;
	scene->actors.length++;

	return actor;
}

void actorFree(Actor *actor)
{
	assert(actor != NULL);

	for (int i = 0; i < actor->renderables.length; i++) {
		if (actor->renderables.data[i] != NULL) {
			/**
			 * Free child renderables.
			 */
			renderableFree(actor->renderables.data[i]);
			printf("Freeing renderable.\n");
		}
	}
	*actor->parent = NULL;
	free(actor);
}