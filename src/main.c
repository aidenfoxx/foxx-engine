#include <stdio.h>

#include "context.h"
#include "input.h"
#include "renderer.h"
#include "object.h"
#include "Tools/log.h"
#include "Renderer/shader.h"
#include "Object/Mesh/fem.h"

#include <GL/freeglut.h>

ShaderProgram phongShader;
Shader phongVertex;
Shader phongFragment;

Camera camera;
Mesh mesh;
Object model;
Renderer renderer;

int renderInit()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

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

	meshInit(&mesh);
	femLoad(&mesh, NULL, NULL, NULL, "crate.fem");

	objectInit(&model, &mesh, NULL, NULL, NULL);

	rendererAddObject(&renderer, &model, OBJECT_STATIC);

	return 0;
}

void renderDestroy()
{
	rendererDestroy(&renderer);
	shaderProgramDestroy(&phongShader);
	objectDestroy(&model);
}

void keyDownFunction(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		inputSetState(INPUT_KEY_W, INPUT_KEY_PRESS);
	}

	if (key == 'a')
	{
		inputSetState(INPUT_KEY_A, INPUT_KEY_PRESS);
	}

	if (key == 's')
	{
		inputSetState(INPUT_KEY_S, INPUT_KEY_PRESS);
	}

	if (key == 'd')
	{
		inputSetState(INPUT_KEY_D, INPUT_KEY_PRESS);
	}

	if (key == 'q')
	{
		inputSetState(INPUT_KEY_Q, INPUT_KEY_PRESS);
	}

	if (key == 'e')
	{
		inputSetState(INPUT_KEY_E, INPUT_KEY_PRESS);
	}

	if (key == 'z')
	{
		inputSetState(INPUT_KEY_Z, INPUT_KEY_PRESS);
	}

	if (key == 'x')
	{
		inputSetState(INPUT_KEY_X, INPUT_KEY_PRESS);
	}
}

void keyUpFunction(unsigned char key, int x, int y)
{
	if (key == 'w')
	{
		inputSetState(INPUT_KEY_W, INPUT_KEY_RELEASE);
	}

	if (key == 'a')
	{
		inputSetState(INPUT_KEY_A, INPUT_KEY_RELEASE);
	}

	if (key == 's')
	{
		inputSetState(INPUT_KEY_S, INPUT_KEY_RELEASE);
	}

	if (key == 'd')
	{
		inputSetState(INPUT_KEY_D, INPUT_KEY_RELEASE);
	}

	if (key == 'q')
	{
		inputSetState(INPUT_KEY_Q, INPUT_KEY_RELEASE);
	}

	if (key == 'e')
	{
		inputSetState(INPUT_KEY_E, INPUT_KEY_RELEASE);
	}

	if (key == 'z')
	{
		inputSetState(INPUT_KEY_Z, INPUT_KEY_RELEASE);
	}

	if (key == 'x')
	{
		inputSetState(INPUT_KEY_X, INPUT_KEY_RELEASE);
	}
}

void renderFunction()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	rendererExecute(&renderer);

	if (inputGetState(INPUT_KEY_W) == INPUT_KEY_PRESS)
	{
		objectTranslate(&model, 0.0f, 0.0f, 0.001f);
	}

	if (inputGetState(INPUT_KEY_A) == INPUT_KEY_PRESS)
	{
		objectTranslate(&model, 0.001f, 0.0f, 0.0f);
	}

	if (inputGetState(INPUT_KEY_S) == INPUT_KEY_PRESS)
	{
		objectTranslate(&model, 0.0f, 0.0f, -0.001f);
	}

	if (inputGetState(INPUT_KEY_D) == INPUT_KEY_PRESS)
	{
		objectTranslate(&model, -0.001f, 0.0f, 0.0f);
	}

	if (inputGetState(INPUT_KEY_Q) == INPUT_KEY_PRESS)
	{
		objectRotate(&model, 0.001f, 0.0f, 0.0f);
	}

	if (inputGetState(INPUT_KEY_E) == INPUT_KEY_PRESS)
	{
		objectRotate(&model, -0.001f, 0.0f, 0.0f);
	}

	if (inputGetState(INPUT_KEY_Z) == INPUT_KEY_PRESS)
	{
		objectRotate(&model, 0.0f, 0.001f, 0.0f);
	}

	if (inputGetState(INPUT_KEY_X) == INPUT_KEY_PRESS)
	{
		objectRotate(&model, 0.0f, -0.001f, 0.0f);
	}

	glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(1024, 768);
	glutCreateWindow("Foxx Engine");
	glutDisplayFunc(renderFunction);
	glutKeyboardFunc(keyDownFunction);
	glutKeyboardUpFunc(keyUpFunction); 

	if (gl3wInit())
	{
		logMessage(LOG_CRITICAL, "Could not initialize OpenGL.");
		exit(EXIT_FAILURE);
	}

	if (!gl3wIsSupported(3, 3))
	{
		logMessage(LOG_CRITICAL, "Your machine does not support OpenGL 3.3.");
		exit(EXIT_FAILURE);
	}

	if (renderInit())
	{
		exit(EXIT_FAILURE);
	}

	logMessage(LOG_NOTICE, "Program initialized.");
	glutMainLoop();

	logMessage(LOG_NOTICE, "Program terminated.");
	renderDestroy();

	exit(EXIT_SUCCESS);
}