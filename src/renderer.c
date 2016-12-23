#include "renderer.h"

Renderer *rendererNew(Camera *camera)
{
	Renderer *renderer;

	if ((renderer = malloc(sizeof(Renderer))) != NULL)
	{
		renderer->shaders = arrayNew();
		renderer->objects = arrayNew();
		renderer->objectsVAO = arrayNew();
		renderer->shaders = arrayNew();
		renderer->camera = camera;
	}

	return renderer;
}

void rendererFree(Renderer *renderer)
{
	if (renderer)
	{
		int objectsLength = arrayLength(renderer->objects);

		for (int i = 0; i < objectsLength; i++)
		{
			rendererRemoveObject(renderer, i);
		}	

		arrayFree(renderer->objects);
		arrayFree(renderer->objectsVAO);
		free(renderer);
	}
}

int rendererAddShader(Renderer *renderer, ShaderProgram *program)
{
	arrayPush(renderer->shaders, program);
	return arrayLength(renderer->shaders);
}

void rendererRemoveShader(Renderer *renderer, int shaderID)
{
	arrayRemove(renderer->shaders, shaderID - 1);
}

int rendererAddObject(Renderer *renderer, Object *object)
{
	int objectID = -1;

	GLuint *vao;

	if (object && (vao = malloc(sizeof(GLuint))) != NULL)
	{
		glGenVertexArrays(1, vao);
		glBindVertexArray(*vao);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		modelBindProperty(MODEL_VERTICES, objectGetModel(object));
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

		modelBindProperty(MODEL_UVS, objectGetModel(object));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

		modelBindProperty(MODEL_NORMALS, objectGetModel(object));
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
		
		modelUnbind();
		glBindVertexArray(0);

		arrayPush(renderer->objects, object);
		arrayPush(renderer->objectsVAO, vao);

		objectID = arrayLength(renderer->objects);
	}
	
	return objectID;
}

void rendererRemoveObject(Renderer *renderer, int objectID)
{
	GLuint *vao;

	if ((vao = (GLuint*)arrayGet(renderer->objectsVAO, objectID - 1)) != NULL)
	{
		arrayRemove(renderer->objectsVAO, objectID - 1);
		glDeleteVertexArrays(1, vao);
		free(vao);
	}
}

void rendererExecute(Renderer *renderer)
{
	ShaderProgram *program;
	
	int shaderLength = arrayLength(renderer->shaders);
	int objectsLength = arrayLength(renderer->objects);

	for (int i = 0; i < shaderLength; i++)
	{
		if (!(program = (ShaderProgram*)arrayGet(renderer->shaders, i)))
		{
			continue;
		}

		shaderProgramBind(program);

		for (int i = 0; i < objectsLength; i++)
		{
			Object *object = (Object*)arrayGet(renderer->objects, i);
			
			if (object)
			{
				Model *model = objectGetModel(object);

				if (model)
				{
					GLuint *objectVAO = (GLuint*)arrayGet(renderer->objectsVAO, i);

					glBindVertexArray(*objectVAO);

					Mat4 M = objectGetTransform(object);
					Mat4 MV = mat4MultiplyMat4(cameraGetView(renderer->camera), M);
					Mat4 MVP = mat4MultiplyMat4(cameraGetProjection(renderer->camera), MV);

					shaderProgramSetMat4(program, "model", M);
					shaderProgramSetMat4(program, "modelView", MV);
					shaderProgramSetMat4(program, "modelViewProjection", MVP);
					shaderProgramSetMat4(program, "normalMatrix", mat4Transpose(mat4Inverse(MV)));

					Texture *diffuse = objectGetTexture(TEXTURE_DIFFUSE, object);
					Texture *specular = objectGetTexture(TEXTURE_SPECULAR, object);
					Texture *normal = objectGetTexture(TEXTURE_NORMAL, object);
					
					if (diffuse)
					{
						textureBind(TEXTURE_DIFFUSE, diffuse);
					}
					
					if (specular)
					{
						textureBind(TEXTURE_SPECULAR, specular);
					}
					
					if (normal)
					{
						textureBind(TEXTURE_NORMAL, normal);
					}

					modelBindProperty(MODEL_INDICES, model);
					glDrawElements(GL_TRIANGLES, objectGetModel(object)->indicesLength * 3, GL_UNSIGNED_INT, 0);
				}
			}
		}
	}

	modelUnbind();
	textureUnbind();
	shaderProgramUnbind();

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}