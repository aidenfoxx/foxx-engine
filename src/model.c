#include "model.h"

Model *modelNew(Vec3 *vertices, Vec2 *uvs, Vec3 *normals, int *indices, int verticesLength, int uvsLength, int normalsLength, int indicesLength)
{
	Model *model;

	if ((model = malloc(sizeof(Model))) != NULL)
	{
		model->vertices = NULL;
		model->uvs = NULL;
		model->normals = NULL;
		model->indices = NULL;

		model->verticesLength = 0;
		model->uvsLength = 0;
		model->normalsLength = 0;
		model->indicesLength = 0;

		if ((model->vertices = malloc(verticesLength * sizeof(Vec3))) != NULL)
		{
			memcpy(model->vertices, vertices, verticesLength * sizeof(Vec3));
			model->verticesLength = verticesLength;
		}

		if ((model->uvs = malloc(uvsLength * sizeof(Vec2))) != NULL)
		{
			memcpy(model->uvs, uvs, uvsLength * sizeof(Vec2));
			model->uvsLength = uvsLength;
		}

		if ((model->normals = malloc(normalsLength * sizeof(Vec3))) != NULL)
		{
			memcpy(model->normals, normals, normalsLength * sizeof(Vec3));
			model->normalsLength = normalsLength;
		}

		if ((model->indices = malloc(indicesLength * sizeof(int))) != NULL)
		{
			memcpy(model->indices, indices, indicesLength * sizeof(int));
			model->indicesLength = indicesLength;
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