#include "model.h"

Model *modelNew(Vec3 *vertices, 
				Vec2 *uvs, 
				Vec3 *normals, 
				Vec3 *indices,
				int verticesLength, 
				int uvsLength, 
				int normalsLength, 
				int indicesLength)
{
	Model *model;

	if ((model = malloc(sizeof(Model))) != NULL)
	{
		model->vertices = NULL;
		model->uvs = NULL;
		model->normals = NULL;
		model->indices = NULL;

		glGenBuffers(4, model->vbo);

		modelSetProperty(MODEL_VERTICES, model, vertices, verticesLength);
		modelSetProperty(MODEL_UVS, model, uvs, uvsLength);
		modelSetProperty(MODEL_NORMALS, model, normals, normalsLength);
		modelSetProperty(MODEL_INDICES, model, indices, indicesLength);
	}

	return model;
}

Model *modelDuplicate(Model *model)
{
	return modelNew(model->vertices, 
					model->uvs, 
					model->normals, 
					model->indices, 
					model->verticesLength,
					model->uvsLength,
					model->normalsLength,
					model->indicesLength);
}

void modelFree(Model *model)
{
	if (model)
	{
		glDeleteBuffers(4, model->vbo);
		free(model->vertices);
		free(model->uvs);
		free(model->normals);
		free(model->indices);
		free(model);
	}
}

void modelSetProperty(int property, Model *model, void *data, int length)
{
	switch (property)
	{
		case MODEL_VERTICES:
			free(model->vertices);

			if ((model->vertices = malloc(length * sizeof(Vec3))) != NULL)
			{
				model->verticesLength = length;
				
				memcpy(model->vertices, (Vec3*)data, model->verticesLength * sizeof(Vec3));
				modelBindProperty(property, model);
				glBufferData(GL_ARRAY_BUFFER, model->verticesLength * sizeof(Vec3), (float*)model->vertices, GL_STATIC_DRAW);
			}

			break;

		case MODEL_UVS:
			free(model->uvs);

			if ((model->uvs = malloc(length * sizeof(Vec3))) != NULL)
			{
				model->uvsLength = length;

				memcpy(model->uvs, (Vec2*)data, model->uvsLength * sizeof(Vec2));
				modelBindProperty(property, model);
				glBufferData(GL_ARRAY_BUFFER, model->uvsLength * sizeof(Vec2), (float*)model->uvs, GL_STATIC_DRAW);
			}
			
			break;

		case MODEL_NORMALS:
			free(model->normals);

			if ((model->normals = malloc(length * sizeof(Vec3))) != NULL)
			{
				model->normalsLength = length;

				memcpy(model->normals, (Vec3*)data, model->normalsLength * sizeof(Vec3));
				modelBindProperty(property, model);
				glBufferData(GL_ARRAY_BUFFER, model->normalsLength * sizeof(Vec3), (float*)model->normals, GL_STATIC_DRAW);
			}

			break;

		case MODEL_INDICES:
			free(model->indices);

			if ((model->indices = malloc(length * sizeof(Vec3))) != NULL)
			{
				model->indicesLength = length;

				memcpy(model->indices, (Vec3*)data, model->indicesLength * sizeof(Vec3));
				modelBindProperty(property, model);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indicesLength * sizeof(Vec3), (int*)model->indices, GL_STATIC_DRAW);
			}

			break;
	}

	modelUnbind();
}

void *modelGetProperty(int property, Model *model)
{
	switch (property)
	{
		case MODEL_VERTICES:
			return model->vertices;

		case MODEL_UVS:
			return model->uvs;

		case MODEL_NORMALS:
			return model->normals;

		case MODEL_INDICES:
			return model->indices;
	}

	return NULL;
}

int modelGetPropertyLength(int property, Model *model)
{
	switch (property)
	{
		case MODEL_VERTICES:
			return model->verticesLength;

		case MODEL_UVS:
			return model->uvsLength;

		case MODEL_NORMALS:
			return model->normalsLength;

		case MODEL_INDICES:
			return model->indicesLength;
	}

	return -1;
}

void modelBindProperty(int property, Model *model)
{
	switch (property)
	{
		case MODEL_VERTICES:
			glBindBuffer(GL_ARRAY_BUFFER, model->vbo[0]);
			break;

		case MODEL_UVS:
			glBindBuffer(GL_ARRAY_BUFFER, model->vbo[1]);
			break;

		case MODEL_NORMALS:
			glBindBuffer(GL_ARRAY_BUFFER, model->vbo[2]);
			break;

		case MODEL_INDICES:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->vbo[3]);
			break;
	}
}

void modelUnbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}