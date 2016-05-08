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
    if (shaderInit(&defaultVertex, SHADER_VERTEX, "shaders/vertex/default.glsl"))
    {
        char *error = shaderError(&defaultVertex);
        logMessage(LOG_ERROR, "Shader failed to compile with the following error:");
        logMessage(LOG_NONE, error);
    }

    if (shaderInit(&defaultFragment, SHADER_FRAGMENT, "shaders/fragment/default.glsl"))
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
    assetLoadObj(&asset, "./assets/demo.obj");
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

void buttonCallback(int button, int action)
{
    if (button == KEY_W && action == INPUT_PRESS)
    {
        cameraTranslate(&camera, 0.0f, 0.0f, 0.1f);
    }

    if (button == KEY_A && action == INPUT_PRESS)
    {
        cameraTranslate(&camera, 0.1f, 0.0f, 0.0f);
    }

    if (button == KEY_S && action == INPUT_PRESS)
    {
        cameraTranslate(&camera, 0.0f, 0.0f, -0.1f);
    }

    if (button == KEY_D && action == INPUT_PRESS)
    {
        cameraTranslate(&camera, -0.1f, 0.0f, 0.0f);
    }

    if (button == KEY_Q && action == INPUT_PRESS)
    {
        cameraRotate(&camera, 0.1f, 0.0f, 0.0f);
    }

    if (button == KEY_E && action == INPUT_PRESS)
    {
        cameraRotate(&camera, -0.1f, 0.0f, 0.0f);
    }
}

void renderFunction()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    sceneRender(&scene);
}

int main(int argc, const char *argv[])
{    
    if (contextInit(3, 3))
    {
        logMessage(LOG_CRITICAL, "Failed to initialize context.");
        exit(EXIT_FAILURE);
    }

    if (contextWindowOpen("Foxx", 800, 600, 0, 0))
    {
        logMessage(LOG_ERROR, "Failed to open window.");
        exit(EXIT_FAILURE);
    }

    renderInit();

    logMessage(LOG_NOTICE, "Program initialized.");

    inputButtonCallback(buttonCallback);

    contextLoopCallback(renderFunction);
    contextLoop();

    renderDestroy();
    contextDestroy();

    exit(EXIT_SUCCESS);
}