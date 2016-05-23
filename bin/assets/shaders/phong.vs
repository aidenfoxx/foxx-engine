#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 modelView;
uniform mat4 modelViewPerspective;
uniform mat4 normalMatrix;

out vec3 vertexPosition;
out vec3 normalInterp;

void main()
{
    vec4 vertexPosition4 = modelView * vec4(vertex, 1.0);
    vertexPosition = vec3(vertexPosition4) / vertexPosition4.w;
    normalInterp = vec3(normalMatrix * vec4(normal, 0.0));

    gl_Position = modelViewPerspective * vec4(vertex, 1.0);
}