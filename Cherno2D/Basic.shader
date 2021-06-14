#shader vertex
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

#shader fragment
layout(location = 0) out vec4 FragColor;
vec3 lightPos = vec3(0.3f, 0.4f, 0.4f);
uniform vec3 viewPos;
vec3 objectColor = vec3(1.0f, 0.0f, 0.5f);
vec3 lightColor  = vec3(0.0f, 0.70f, 1.0f);
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
uniform sampler2D ourTexture;
float constant;
float linear;
float quadratic;
void main()
{
	float specularStrength = 1.0;
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	// diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;
	
	vec3 result = ambient + diffuse + specular;
	//FragColor = texture(ourTexture, TexCoord);
	FragColor = vec4(result, 1.0);
};










