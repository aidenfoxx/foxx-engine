#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 texture;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec3 index;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 perspectiveMatrix;

void main()
{
	gl_Position = perspectiveMatrix * viewMatrix * modelMatrix * vec4(vertex, 1.0);
}