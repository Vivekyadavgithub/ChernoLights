#version 430 core
layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * position;
};