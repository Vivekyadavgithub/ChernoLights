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