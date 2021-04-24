#shader vertex
#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 FragPos;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	FragPos = vec3(model * vec4(position, 1.0));
	Normal = aNormal;
	gl_Position = projection * view  * vec4(FragPos, 1.0f);
};

#shader fragment
#version 430 core

layout(location = 0) out vec4 FragColor;
vec3 lightPos = vec3(1.0f, 1.0f, 0.3f);
vec3 objectColor = vec3(0.9f, 0.9f, 0.5f);
vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
in vec3 FragPos;
in vec3 Normal;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 result = (ambient + diffuse) * objectColor;
	FragColor = vec4(result, 1.0);
}