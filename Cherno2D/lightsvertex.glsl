#version 430 core
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 texCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vec3 FragPos = vec3(model * vec4(position, 1.0));
	gl_Position = projection * view  * vec4(FragPos, 1.0f);
};