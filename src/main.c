#include <stdio.h>

#include "context.h"
#include "input.h"
#include "renderer.h"
#include "object.h"
#include "Object/Mesh/obj.h"
#include "Renderer/shader.h"
#include "Tools/log.h"

ShaderProgram phongShader;
Shader phongVertex;
Shader phongFragment;

Camera camera;
Obj mesh;
Object model;
Renderer renderer;

int renderInit()
{
	/**
	 * Initialize renderer.
	 */
	cameraInit(&camera);

	if (rendererInit(&renderer, &camera))
	{
		logMessage(LOG_ERROR, "There was a problem initializing the renderer.");
		rendererDestroy(&renderer);
		return -1;
	}

	/**
	 * Initialize shaders.
	 */
	shaderProgramInit(&phongShader);

	if (shaderInit(&phongVertex, SHADER_VERTEX, "./assets/shaders/phong.vs"))
	{
		char *error = shaderError(&phongVertex); 
		logMessage(LOG_ERROR, "Failed to compile vertex shader with the following error(s):"); 
		logMessage(LOG_NONE, error);
		return -2;
	}

	if (shaderInit(&phongFragment, SHADER_FRAGMENT, "./assets/shaders/phong.fs"))
	{
		char *error = shaderError(&phongFragment); 
		logMessage(LOG_ERROR, "Failed to compile fragment shader with the following error(s):"); 
		logMessage(LOG_NONE, error);
		return -2;
	}

	shaderAttach(&phongShader, &phongVertex);
	shaderAttach(&phongShader, &phongFragment);

	if (shaderProgramLink(&phongShader))
	{
		char *error = shaderProgramError(&phongShader); 
		logMessage(LOG_ERROR, "Failed to link shader with the following error(s):"); 
		logMessage(LOG_NONE, error);
		return -3;
	}

	rendererAddShader(&renderer, &phongShader);

	shaderDestroy(&phongVertex);
	shaderDestroy(&phongFragment);

	if (objInit(&mesh, "./assets/models/suzanne.obj"))
	{
		logMessage(LOG_ERROR, "There was a problem loading the model.");
		return -4;
	}

	/*printf("OBJ Verts: %i\n", mesh.verticesLength);
	printf("UVs Verts: %i\n", mesh.uvsLength);
	printf("Normals Verts: %i\n", mesh.normalsLength);
	printf("Indices Verts: %i\n", mesh.indicesLength);

	for (int i = 0; i < mesh.verticesLength; ++i)
	{
		printf("%f %f %f\n", mesh.vertices[i].x, mesh.vertices[i].y, mesh.vertices[i].z);
	}*/

	objectInit(&model, &mesh, NULL, NULL, NULL);
	rendererAddObject(&renderer, &model, OBJECT_STATIC);

	return 0;
}

void renderDestroy()
{
	rendererDestroy(&renderer);
	shaderProgramDestroy(&phongShader);
	objectDestroy(&model);
	objDestroy(&mesh);
}

void inputHandle()
{
	if (inputStatusKey(KEY_W) & (INPUT_PRESS | INPUT_HOLD))
	{
		cameraTranslate(&camera, 0.0f, 0.0f, 0.05f);
	}

	if (inputStatusKey(KEY_A) & (INPUT_PRESS | INPUT_HOLD))
	{
		cameraTranslate(&camera, 0.05f, 0.0f, 0.0f);
	}

	if (inputStatusKey(KEY_S) & (INPUT_PRESS | INPUT_HOLD))
	{
		cameraTranslate(&camera, 0.0f, 0.0f, -0.05f);
	}

	if (inputStatusKey(KEY_D) & (INPUT_PRESS | INPUT_HOLD))
	{
		cameraTranslate(&camera, -0.05f, 0.0f, 0.0f);
	}

	if (inputStatusKey(KEY_Q) & (INPUT_PRESS | INPUT_HOLD))
	{
		cameraRotate(&camera, 0.05f, 0.0f, 0.0f);
	}

	if (inputStatusKey(KEY_E) & (INPUT_PRESS | INPUT_HOLD))
	{
		cameraRotate(&camera, -0.05f, 0.0f, 0.0f);
	}
}

void errorFunction(int errorCode, const char *errorMessage)
{
	char errorCodeMessage[256];
	snprintf(errorCodeMessage, 256, "Context returned error %i:", errorCode);

	logMessage(LOG_ERROR, errorCodeMessage);
	logMessage(LOG_NONE, errorMessage);
}

void renderFunction()
{
	inputHandle();
	rendererExecute(&renderer);
}

int main(int argc, const char *argv[])
{
	if (contextInit(3, 3))
	{
		logMessage(LOG_CRITICAL, "Failed to initialize context.");
		exit(EXIT_FAILURE);
	}

	if (contextWindowOpen("Foxx", 1024, 800, 0, 1))
	{
		logMessage(LOG_ERROR, "Failed to open window.");
		exit(EXIT_FAILURE);
	}

	inputInit();
	
	if (!renderInit())
	{
		logMessage(LOG_NOTICE, "Program initialized.");
		contextLoopCallback(renderFunction);
		contextLoop();
	}

	renderDestroy();
	contextDestroy();

	exit(EXIT_SUCCESS);
}