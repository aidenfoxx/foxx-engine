#include "renderer/renderable.h"

Renderable *renderableNew(Actor *actor, RenderableGeometry *geometry, RenderableMaterial *material)
{
	assert(actor != NULL);

	Renderable *renderable = malloc(sizeof(Renderable));

	renderable->parent = (void**)&actor->renderables.data[actor->renderables.length];
	renderable->geometry = geometry;
	renderable->material = material;
	renderable->translation = vec3(0.0f, 0.0f, 0.0f);
	renderable->rotation = vec4(0.0f, 0.0f, 0.0f, 1.0f);
	renderable->scale = vec3(1.0f, 1.0f, 1.0f);
	renderable->transform = mat4MultiplyMat4(
		mat4Translation(renderable->translation),
		mat4MultiplyMat4(
			mat4RotationQuat(renderable->rotation),
			mat4Scale(renderable->scale)	
		)
	);
	renderable->aabb.min = vec3(-0.5f, -0.5f, -0.5f);
	renderable->aabb.max = vec3(0.5f, 0.5f, 0.5f);

	actor->renderables.data[actor->renderables.length] = renderable;
	actor->renderables.length++;

	return renderable;
}

void renderableFree(Renderable *renderable)
{
	assert(renderable != NULL);

	*renderable->parent = NULL;
	free(renderable);
}