#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;

out vec3 vertexPosition;
out vec3 normalInterp;

void main()
{
	mat4 normalMatrix = transpose(inverse(viewMatrix * modelMatrix));

    vec4 vertexPosition4 = viewMatrix * modelMatrix * vec4(vertex, 1.0);
    vertexPosition = vec3(vertexPosition4) / vertexPosition4.w;
    normalInterp = vec3(normalMatrix * vec4(normal, 0.0));

    gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.0);
}