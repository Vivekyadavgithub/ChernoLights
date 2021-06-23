layout(location = 0) in vec3 position;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 texCoords;

out vec3 Normal;
out vec3 FragPos;
out vec2 TexCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{	
	FragPos = vec3(model * vec4(position, 1.0));
	TexCoord = texCoords;
	Normal = aNormal;
	gl_Position = projection * view  * vec4(FragPos, 1.0f);
};