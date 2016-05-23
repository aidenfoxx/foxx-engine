#include <stdio.h>

#include "context.h"
#include "input.h"
#include "shader.h"
#include "scene.h"

#include "Assets/obj.h"
#include "Tools/log.h"

ShaderProgram phongShader;
Shader phongVertex;
Shader phongFragment;

Asset asset;
Prop prop;
Camera camera;
Scene scene;

int renderInit()
{
	/**
	 * Initialize scene and add props and shader.
	 */
	cameraInit(&camera);

	if (sceneInit(&scene, &camera))
	{
		logMessage(LOG_ERROR, "There was a problem initializing the scene.");
		sceneDestroy(&scene);
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
	}

	if (shaderInit(&phongFragment, SHADER_FRAGMENT, "./assets/shaders/phong.fs"))
	{
		char *error = shaderError(&phongFragment); 
		logMessage(LOG_ERROR, "Failed to compile fragment shader with the following error(s):"); 
		logMessage(LOG_NONE, error);
	}

	shaderAttach(&phongShader, &phongVertex);
	shaderAttach(&phongShader, &phongFragment);

	if (shaderProgramLink(&phongShader))
	{
		char *error = shaderProgramError(&phongShader); 
		logMessage(LOG_ERROR, "Failed to link shader with the following error(s):"); 
		logMessage(LOG_NONE, error);
	}

	sceneAddShader(&scene, &phongShader);

	shaderDestroy(&phongVertex);
	shaderDestroy(&phongFragment);

	/**
	 * Load models and bind them to a prop.
	 */
	Obj model;

	if (objInit(&model, "./assets/models/buddha.obj"))
	{
		logMessage(LOG_ERROR, "There was a problem loading the model.");
	}
	else
	{
		assetInit(&asset);

		if (assetBindObj(&asset, &model))
		{
			logMessage(LOG_ERROR, "There was a problem binding the model mesh.");
			assetDestroy(&asset);
		}
		else
		{
			propInit(&prop, &asset);
			sceneAddProp(&scene, &prop);
			
		}
	}

	objDestroy(&model);

	return 0;
}

void renderDestroy()
{
	sceneDestroy(&scene);
	propDestroy(&prop);
	assetDestroy(&asset);
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