#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "context.h"
#include "input.h"
#include "renderer.h"
#include "object.h"
#include "Tools/log.h"
#include "Renderer/shader.h"
#include "Object/fem.h"

#include <GL/freeglut.h>

#define RENDER_WIDTH 1024
#define RENDER_HEIGHT 768

ShaderProgram *phongShader;

Array *objects;
Camera *camera;
Renderer *renderer;

int mouseStartX = -1;
int mouseStartY = -1;

void renderFree()
{
	for (int i = 0; i < arrayLength(objects); i++)
	{
		objectFemFree((Object*)arrayGet(objects, i));
	}

	/**
	 * TODO: Test overlapping frees.
	 */
	arrayFree(objects);
	rendererFree(renderer);
	cameraFree(camera);
	shaderProgramFree(phongShader);
}

int renderInit()
{
	/**
	 * GL Init
	 */
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glDepthFunc(GL_LEQUAL);
	glCullFace(GL_FRONT);
	glFrontFace(GL_CW);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	camera = cameraPerspectiveNew(1.0f, (float)RENDER_WIDTH / (float)RENDER_HEIGHT);
	cameraSetTranslation(camera, vec3(0.0f, 0.0f, -5.0f));

	renderer = rendererNew(camera);

	/**
	 * Initialize renderer.
	 */
	if (camera == NULL || renderer == NULL)
	{
		logMessage(LOG_ERROR, "There was a problem initializing the renderer.");
		renderFree();
		return -1;
	}

	/**
	 * Initialize shaders.
	 */
	Shader *phongVertex = shaderLoad(SHADER_VERTEX, "./assets/shaders/phong.vert");
	Shader *phongFragment = shaderLoad(SHADER_FRAGMENT, "./assets/shaders/phong.frag");

	phongShader = shaderProgramNew();

	if (phongVertex == NULL || phongFragment == NULL || phongShader == NULL)
	{
		logMessage(LOG_ERROR, "Failed to load shader(s)."); 
		renderFree();
		return -1;
	}

	if (shaderError(phongVertex))
	{
		logMessage(LOG_ERROR, "Failed to compile vertex shader with the following error(s):"); 
		logMessage(LOG_NONE, shaderError(phongVertex));
		renderFree();
		return -1;
	}

	if (shaderError(phongFragment))
	{
		logMessage(LOG_ERROR, "Failed to compile fragment shader with the following error(s):"); 
		logMessage(LOG_NONE, shaderError(phongFragment));
		renderFree();
		return -1;
	}

	shaderProgramAttach(phongShader, phongVertex);
	shaderProgramAttach(phongShader, phongFragment);

	if (shaderProgramLink(phongShader))
	{
		logMessage(LOG_ERROR, "Failed to link shader with the following error(s):"); 
		logMessage(LOG_NONE, shaderProgramError(phongShader));
		renderFree();
		return -1;
	}

	shaderFree(phongVertex);
	shaderFree(phongFragment);

	/**
	 * Add entities to renderer.
	 */
	Object *crate = objectFemLoad("assets/models/crate.fem");
	Object *teapot = objectFemLoad("assets/models/monkey.fem");

	objects = arrayNew();
	arrayPush(objects, crate);
	arrayPush(objects, teapot);

	objectSetTranslation(crate, vec3(2.0f, 0.0f, 0.0f));
	objectSetTranslation(teapot, vec3(-2.0f, 0.0f, 0.0f));

	rendererAddShader(renderer, phongShader);
	rendererAddObject(renderer, teapot);
	rendererAddObject(renderer, crate);
	
	return 0;
}

struct timeval previousTime;

float delta = 1000000.0f / 60.0f;
float accumulator = 0;

void renderFunction()
{
	int frameTime;
	struct timeval currentTime;

	gettimeofday(&currentTime, NULL);

	/**
	 * gettimeofday can return a decreasing
	 * time.
	 */
	if ((frameTime = currentTime.tv_usec - previousTime.tv_usec) < 0)
		frameTime = 0;

	accumulator += frameTime / delta;
	previousTime = currentTime;

	while (accumulator >= 1.0f)
	{
		accumulator -= 1.0f;

		if (inputGetState(INPUT_KEY_W) == INPUT_PRESS)
		{
			cameraTranslate(camera, vec3(0.0f, 0.0f, -0.1f));
		}

		if (inputGetState(INPUT_KEY_A) == INPUT_PRESS)
		{
			cameraTranslate(camera, vec3(0.1f, 0.0f, 0.0f));
		}

		if (inputGetState(INPUT_KEY_S) == INPUT_PRESS)
		{
			cameraTranslate(camera, vec3(0.0f, 0.0f, 0.1f));
		}

		if (inputGetState(INPUT_KEY_D) == INPUT_PRESS)
		{
			cameraTranslate(camera, vec3(-0.1f, 0.0f, 0.0f));
		}

		if (inputGetState(INPUT_KEY_Q) == INPUT_PRESS)
		{
			cameraTranslate(camera, vec3(0.0f, 0.1f, 0.0f));
		}

		if (inputGetState(INPUT_KEY_E) == INPUT_PRESS)
		{
			cameraTranslate(camera, vec3(0.0f, -0.1f, 0.0f));
		}

		if (inputGetState(INPUT_MOUSE_LEFT) == INPUT_PRESS)
		{
			if (mouseStartX == -1 && mouseStartY == -1)
			{
				mouseStartX = inputGetState(INPUT_MOUSE_X);
				mouseStartY = inputGetState(INPUT_MOUSE_Y);
			}

			int maxRotation = 1.570795;

			int mouseX = inputGetState(INPUT_MOUSE_X);
			int mouseY = inputGetState(INPUT_MOUSE_Y);

			float rotationX = ((float)(mouseX - mouseStartX) / (float)(RENDER_WIDTH / 2)) * maxRotation;
			float rotationY = ((float)(mouseY - mouseStartY) / (float)(RENDER_HEIGHT / 2)) * maxRotation;

			cameraRotate(camera, vec3(rotationY, rotationX, 0.0f));

			mouseStartX = mouseX;
			mouseStartY = mouseY;
		}

		if (inputGetState(INPUT_MOUSE_LEFT) == INPUT_RELEASE && (mouseStartX != -1 || mouseStartY != -1))
		{
			mouseStartX = -1;
			mouseStartY = -1;
		}
    }

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	rendererExecute(renderer);
	
	glutSwapBuffers();
	glutPostRedisplay();
}

void keyDownFunction(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			inputSetState(INPUT_KEY_W, INPUT_PRESS, INPUT_NULL);
			break;

		case 'a':
			inputSetState(INPUT_KEY_A, INPUT_PRESS, INPUT_NULL);
			break;

		case 's':
			inputSetState(INPUT_KEY_S, INPUT_PRESS, INPUT_NULL);
			break;

		case 'd':
			inputSetState(INPUT_KEY_D, INPUT_PRESS, INPUT_NULL);
			break;

		case 'q':
			inputSetState(INPUT_KEY_Q, INPUT_PRESS, INPUT_NULL);
			break;

		case 'e':
			inputSetState(INPUT_KEY_E, INPUT_PRESS, INPUT_NULL);
			break;

		case 'z':
			inputSetState(INPUT_KEY_Z, INPUT_PRESS, INPUT_NULL);
			break;

		case 'x':
			inputSetState(INPUT_KEY_X, INPUT_PRESS, INPUT_NULL);
			break;
	}
}

void keyUpFunction(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			inputSetState(INPUT_KEY_W, INPUT_RELEASE, INPUT_NULL);
			break;

		case 'a':
			inputSetState(INPUT_KEY_A, INPUT_RELEASE, INPUT_NULL);
			break;

		case 's':
			inputSetState(INPUT_KEY_S, INPUT_RELEASE, INPUT_NULL);
			break;

		case 'd':
			inputSetState(INPUT_KEY_D, INPUT_RELEASE, INPUT_NULL);
			break;

		case 'q':
			inputSetState(INPUT_KEY_Q, INPUT_RELEASE, INPUT_NULL);
			break;

		case 'e':
			inputSetState(INPUT_KEY_E, INPUT_RELEASE, INPUT_NULL);
			break;

		case 'z':
			inputSetState(INPUT_KEY_Z, INPUT_RELEASE, INPUT_NULL);
			break;

		case 'x':
			inputSetState(INPUT_KEY_X, INPUT_RELEASE, INPUT_NULL);
			break;
	}
}

void mouseClickFunction(int button, int state, int x, int y)
{
	switch (button)
	{
		case GLUT_LEFT_BUTTON:
			inputSetState(INPUT_MOUSE_LEFT, state ? INPUT_RELEASE : INPUT_PRESS, INPUT_NULL);
			break;

		case GLUT_MIDDLE_BUTTON:
			inputSetState(INPUT_MOUSE_MIDDLE, state ? INPUT_RELEASE : INPUT_PRESS, INPUT_NULL);
			break;

		case GLUT_RIGHT_BUTTON:
			inputSetState(INPUT_MOUSE_RIGHT, state ? INPUT_RELEASE : INPUT_PRESS, INPUT_NULL);
			break;
	}
}

void mouseMotionFunction(int x, int y)
{
	inputSetState(INPUT_MOUSE_X, INPUT_MOVE, x);
	inputSetState(INPUT_MOUSE_Y, INPUT_MOVE, y);
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(RENDER_WIDTH, RENDER_HEIGHT);
	glutCreateWindow("Foxx Engine");

	glutDisplayFunc(renderFunction);
	glutKeyboardFunc(keyDownFunction);
	glutKeyboardUpFunc(keyUpFunction); 
	glutMouseFunc(mouseClickFunction); 
	glutMotionFunc(mouseMotionFunction); 
	glutPassiveMotionFunc(mouseMotionFunction); 

	if (gl3wInit())
	{
		logMessage(LOG_CRITICAL, "Failed to initialize OpenGL.");
		exit(EXIT_FAILURE);
	}

	if (!gl3wIsSupported(3, 3))
	{
		logMessage(LOG_CRITICAL, "Your machine does not support OpenGL 3.3.");
		exit(EXIT_FAILURE);
	}

	if (renderInit())
	{
		logMessage(LOG_NONE, "Failed to initialize renderer.");
		exit(EXIT_FAILURE);
	}

	logMessage(LOG_NOTICE, "Program initialized.");
	gettimeofday(&previousTime, NULL);
	glutMainLoop();

	logMessage(LOG_NOTICE, "Program terminated.");
	renderFree();

	exit(EXIT_SUCCESS);
}