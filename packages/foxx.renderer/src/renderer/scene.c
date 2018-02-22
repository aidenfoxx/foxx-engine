#include "renderer/scene.h"

Scene *sceneNew(Camera *camera, Shader *shader)
{
	Scene *scene = malloc(sizeof(Scene));

	scene->camera = camera;
	scene->shader = shader;
	/**
	 * TODO: Finder better solution that fixed
	 * size arrays.
	 */
	scene->actors.data = malloc(128 * sizeof(Actor*));
	scene->actors.length = 0;
	
	return scene;
}

void sceneFree(Scene *scene)
{
	assert(scene != NULL);

	for (int i = 0; i < scene->actors.length; i++) {

		if (scene->actors.data[i] != NULL) {
			/**
			 * Free child actors.
			 */
			actorFree(scene->actors.data[i]);
			printf("Freeing actor.\n");
		}
	}
	free(scene);
}

void sceneStep(Scene *scene)
{
	assert(scene != NULL);

	Camera *camera = scene->camera;
	Shader *shader = scene->shader;

	glUseProgram(shader->program);

	for (unsigned a = 0; a < scene->actors.length; a++) {
		Actor *actor;

		if ((actor = scene->actors.data[a]) != NULL) {
			for (unsigned r = 0; r < actor->renderables.length; r++) {
				Renderable *renderable;

				if ((renderable = actor->renderables.data[r]) != NULL) {
					RenderableGeometry *geometry;
					
					if ((geometry = renderable->geometry) != NULL) {
						RenderableMaterial *material;

						if ((material = renderable->material) != NULL) {
							/**
							 * Handle material
							 */
						}

						/**
						 * Handle geometry
						 */
						Mat4 MV = mat4MultiplyMat4(mat4MultiplyMat4(renderable->transform, actor->transform), camera->transform);
						Mat4 MVP = mat4MultiplyMat4(MV, camera->projection);
						Mat4 MV_T = mat4Transpose(MV);
						Mat4 MV_TI = mat4Inverse(MV_T);

						glUniformMatrix4fv(glGetUniformLocation(shader->program, "MV"), 1, GL_FALSE, (const GLfloat*)&MV);
						glUniformMatrix4fv(glGetUniformLocation(shader->program, "MVP"), 1, GL_FALSE, (const GLfloat*)&MVP);
						glUniformMatrix4fv(glGetUniformLocation(shader->program, "MV_T"), 1, GL_FALSE, (const GLfloat*)&MV_T);
						glUniformMatrix4fv(glGetUniformLocation(shader->program, "MV_TI"), 1, GL_FALSE, (const GLfloat*)&MV_TI);

						glBindVertexArray(geometry->vao);
						glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->vbo[3]);
						glDrawElements(GL_TRIANGLES, geometry->indices, GL_UNSIGNED_INT, 0);

						/**
						 * Loop through the 6 planes of the view frustum.
						 */
//						for (unsigned p = 0; p < 6; p++) {
//							float dot = max(renderable->aabb.min.x * camera->plane[p].x, renderable->aabb.max.x * camera->plane[p].x) + 
//									  	max(renderable->aabb.min.y * camera->plane[p].y, renderable->aabb.max.y * camera->plane[p].y) +
//									 	max(renderable->aabb.min.z * camera->plane[p].z, renderable->aabb.max.z * camera->plane[p].z);
//
//							if (dot > -camera->plane[p].w) {
//								printf("Inside frustum.\n");
//								break;
//							} else {
//								printf("Outside plane %u.\n", p);
//							} 
//						}
					}
				}
			}
		}
	}

	glUseProgram(0);
}