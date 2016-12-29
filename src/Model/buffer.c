#include "Model/buffer.h"

ModelBuffer *modelBufferNew(Model *model)
{
	ModelBuffer *modelBuffer;

	if (model && (modelBuffer = malloc(sizeof(ModelBuffer))) != NULL)
	{
		modelBuffer->model = model;

		glGenBuffers(4, modelBuffer->vbo);

		modelBufferBind(modelBuffer, MODEL_VERTICES);
		glBufferData(GL_ARRAY_BUFFER, model->verticesLength * sizeof(Vec3), (float*)model->vertices, GL_STATIC_DRAW);

		modelBufferBind(modelBuffer, MODEL_UVS);
		glBufferData(GL_ARRAY_BUFFER, model->uvsLength * sizeof(Vec2), (float*)model->uvs, GL_STATIC_DRAW);

		modelBufferBind(modelBuffer, MODEL_NORMALS);
		glBufferData(GL_ARRAY_BUFFER, model->normalsLength * sizeof(Vec3), (float*)model->normals, GL_STATIC_DRAW);

		modelBufferBind(modelBuffer, MODEL_INDICES);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, model->indicesLength * sizeof(int), model->indices, GL_STATIC_DRAW);

		modelBufferUnbind();
	}

	return modelBuffer;
}

void modelBufferFree(ModelBuffer *modelBuffer)
{
	if (modelBuffer)
	{
		glDeleteBuffers(4, modelBuffer->vbo);
		free(modelBuffer);
	}
}

Model *modelBufferGetModel(ModelBuffer *modelBuffer)
{
	return modelBuffer->model;
}

void modelBufferBind(ModelBuffer *modelBuffer, int property)
{
	switch (property)
	{
		case MODEL_VERTICES:
			glBindBuffer(GL_ARRAY_BUFFER, modelBuffer->vbo[0]);
			break;

		case MODEL_UVS:
			glBindBuffer(GL_ARRAY_BUFFER, modelBuffer->vbo[1]);
			break;

		case MODEL_NORMALS:
			glBindBuffer(GL_ARRAY_BUFFER, modelBuffer->vbo[2]);
			break;

		case MODEL_INDICES:
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, modelBuffer->vbo[3]);
			break;
	}
}

void modelBufferUnbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}