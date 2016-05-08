#include <stdio.h>

#include "context.h"
#include "input.h"
#include "shader.h"
#include "scene.h"
#include "Scene/camera.h"
#include "Scene/prop.h"
#include "Scene/actor.h"
#include "Tools/log.h"

Asset asset;
Prop prop;
Camera camera;
Scene scene;

ShaderProgram shaderProgram;
Shader defaultVertex;
Shader defaultFragment;

void init()
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
     * Load model and bind it to our
     * actors and props.
     */
    assetInit(&asset);
    assetLoadObj(&asset, "./assets/demo.obj");
    propInit(&prop, &asset);
    
    /**
     * Initialize and fill scene.
     */
    cameraInit(&camera);
    sceneInit(&scene, &camera, &shaderProgram);
    sceneAddProp(&scene, &prop);
}

void destroy()
{
    sceneDestroy(&scene);
    propDestroy(&prop);
    assetDestroy(&asset);
    shaderDestroy(&defaultVertex);
    shaderDestroy(&defaultFragment);
    shaderProgramDestroy(&shaderProgram);
}

void keyCallback(Window keyWindow, int key, int scancode, int action, int mods)
{
    if (key == KEY_W && action == INPUT_PRESS)
    {
        cameraTranslate(&camera, 0.0f, 0.0f, 0.1f);
    }

    if (key == KEY_A && action == INPUT_PRESS)
    {
        cameraTranslate(&camera, 0.1f, 0.0f, 0.0f);
    }

    if (key == KEY_S && action == INPUT_PRESS)
    {
        cameraTranslate(&camera, 0.0f, 0.0f, -0.1f);
    }

    if (key == KEY_D && action == INPUT_PRESS)
    {
        cameraTranslate(&camera, -0.1f, 0.0f, 0.0f);
    }

    if (key == KEY_Q && action == INPUT_PRESS)
    {
        cameraRotate(&camera, 0.1f, 0.0f, 0.0f);
    }

    if (key == KEY_E && action == INPUT_PRESS)
    {
        cameraRotate(&camera, -0.1f, 0.0f, 0.0f);
    }
}

int main(int argc, const char *argv[])
{
    Window window;
    
    if (contextInit(3, 3))
    {
        logMessage(LOG_CRITICAL, "Failed to initialize context.");
        exit(EXIT_FAILURE);
    }

    if (contextWindowOpen(&window, "Foxx", 800, 600, 0, 0))
    {
        logMessage(LOG_ERROR, "Failed to open window.");
        exit(EXIT_FAILURE);
    }

    glClearColor(0.74f, 0.89f, 0.88f, 0.0f);

    init();
    inputSetKeyCallback(&window, keyCallback);

    logMessage(LOG_NOTICE, "Program initialized.");

    while (!contextWindowShouldClose(&window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        sceneRender(&scene);
        contextWindowTick(&window);
    }

    destroy();

    contextWindowDestroy(&window);
    contextDestroy();

    exit(EXIT_SUCCESS);
}