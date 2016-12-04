#include "model.h"

Model *modelNew(int verticesLength, 
				int uvsLength, 
				int normalsLength, 
				int indicesLength,
				Vec3 *vertices, 
				Vec2 *uvs, 
				Vec3 *normals, 
				Vec3 *indices)
{
	Model *model;

	if ((model = malloc(sizeof(Model))) != NULL)
	{
		model->verticesLength = verticesLength;
		model->uvsLength = uvsLength;
		model->normalsLength = normalsLength;
		model->indicesLength = indicesLength;
		
		model->vertices = NULL;
		model->uvs = NULL;
		model->normals = NULL;
		model->indices = NULL;

		/**
		 * Copy the data to save us managing
		 * it elsewhere.
		 */
		if ((model->vertices = malloc(model->verticesLength * sizeof(Vec3))) &&
			(model->uvs = malloc(model->uvsLength * sizeof(Vec2))) &&
			(model->normals = malloc(model->normalsLength * sizeof(Vec3))) &&
			(model->indices = malloc(model->indicesLength * sizeof(Vec3))))
		{
			memcpy(model->vertices, vertices, model->verticesLength * sizeof(Vec3));
			memcpy(model->uvs, uvs, model->uvsLength * sizeof(Vec2));
			memcpy(model->normals, normals, model->normalsLength * sizeof(Vec3));
			memcpy(model->indices, indices, model->indicesLength * sizeof(Vec3));
		}
	}

	return model;
}

void modelFree(Model *model)
{
	if (model)
	{
		free(model->vertices);
		free(model->uvs);
		free(model->normals);
		free(model->indices);
		free(model);
	}
}