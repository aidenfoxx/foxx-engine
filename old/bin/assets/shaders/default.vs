#version 330 core

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec2 uv;
layout (location = 2) in vec3 normal;

uniform mat4 modelViewPerspective;

void main()
{
	gl_Position = modelViewPerspective * vec4(vertex, 1.0);
}