#include <stdio.h>

#include "foxx.h"

ShaderProgram shaderProgram;
Shader defaultVertex;
Shader defaultFragment;

Asset asset;
Prop prop;
Camera camera;
Scene scene;

void renderInit()
{
	/**
	 * Initialize shaders.
	 */
	if (shaderInit(&defaultVertex, SHADER_VERTEX, "./assets/shaders/vertex/default.glsl"))
	{
		char *error = shaderError(&defaultVertex);
		logMessage(LOG_ERROR, "Shader failed to compile with the following error:");
		logMessage(LOG_NONE, error);
	}

	if (shaderInit(&defaultFragment, SHADER_FRAGMENT, "./assets/shaders/fragment/default.glsl"))
	{
		char *error = shaderError(&defaultVertex);
		logMessage(LOG_ERROR, "Shader failed to compile with the following error:");
		logMessage(LOG_NONE, error);
	}

	shaderProgramInit(&shaderProgram);
	shaderAttach(&shaderProgram, &defaultVertex);
	shaderAttach(&shaderProgram, &defaultFragment);

	if (shaderProgramLink(&shaderProgram))
	{
		char *error = shaderProgramError(&shaderProgram);
		logMessage(LOG_ERROR, "Failed to link shader program with the following error:");
		logMessage(LOG_NONE, error);
	}

	/**
	 * Load models and bind them to a prop.
	 */
	assetInit(&asset);

	if (assetLoadObj(&asset, "./assets/models/teapot.obj"))
	{
		logMessage(LOG_ERROR, "There was a problem loading the model.");
	}

	/*printf("Vertex data: \n");

	for (int i = 0; i < asset.vertexLength; i++)
	{
		printf("%f %f %f\n", asset.vertexData[i].x, asset.vertexData[i].y, asset.vertexData[i].z);
	}

	printf("Texture data: \n");

	for (int i = 0; i < asset.textureLength; i++)
	{
		printf("%f %f\n", asset.textureData[i].x, asset.textureData[i].y);
	}

	printf("Normal data: \n");

	for (int i = 0; i < asset.normalLength; i++)
	{
		printf("%f %f %f\n", asset.normalData[i].x, asset.normalData[i].y, asset.normalData[i].z);
	}

	printf("Index data: \n");

	for (int i = 0; i < asset.indexLength; i++)
	{
		printf("%i %i %i\n", asset.indexData[i].x, asset.indexData[i].y, asset.indexData[i].z);
	}*/


	propInit(&prop, &asset);

	/**
	 * Initialize scene and add props and shader.
	 */
	cameraInit(&camera);
	sceneInit(&scene, &camera, &shaderProgram);
	sceneAddProp(&scene, &prop);
}

void renderDestroy()
{
	sceneDestroy(&scene);
	propDestroy(&prop);
	assetDestroy(&asset);
	shaderDestroy(&defaultVertex);
	shaderDestroy(&defaultFragment);
	shaderProgramDestroy(&shaderProgram);
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

void renderFunction()
{
	inputHandle();
	sceneRender(&scene);
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
	renderInit();

	logMessage(LOG_NOTICE, "Program initialized.");

	contextLoopCallback(renderFunction);
	contextLoop();

	renderDestroy();
	contextDestroy();

	exit(EXIT_SUCCESS);
}