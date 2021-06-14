#shader vertex
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

#shader fragment
#version 430 core
out vec4 FragColor;

void main()
{
    vec3 lightColor = vec3(0.5f, 0.5f, 0.1f);
    float ambientStrength = 0.5;
    vec3 ambient = ambientStrength * lightColor;
    vec3 result = ambient * vec3(0.6f);
    FragColor = vec4(result, 1.0); // set alle 4 vector values to 1.0
}
