#version 330 core

const vec3 diffuseColor = vec3(0.8, 0.8, 0.8);

out vec3 gl_FragColor;

void main()
{
    gl_FragColor = diffuseColor;
}