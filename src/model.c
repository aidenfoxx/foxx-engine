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
	Model *model = NULL;

	if ((model = malloc(sizeof(Model))) != NULL)
	{
		model->verticesLength = verticesLength;
		model->uvsLength = uvsLength;
		model->normalsLength = normalsLength;
		model->indicesLength = indicesLength;

		model->vertices = vertices;
		model->uvs = uvs;
		model->normals = normals;
		model->indices = indices;
	}

	return model;
}

void modelFree(Model *model)
{
	if (model)
	{
		free(model);
	}
}