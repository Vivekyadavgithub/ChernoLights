layout(location = 0) out vec4 FragColor;

vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);
vec3 lightAmbient = vec3(0.2f, 0.2f, 0.2f);
vec3 lightdiffuse = vec3(0.5f, 0.5f, 0.5f);
vec3 lightspecular = vec3(0.5f, 0.5f, 0.5f);
uniform vec3 viewPos;
vec3 objectColor = vec3(1.0f, 0.0f, 0.5f);
vec3 lightColor  = vec3(0.0f, 0.70f, 1.0f);
in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
uniform sampler2D ourTexture;
float constant = 1.0f;
float linea = 0.09f;
float quadratic = 0.032f;
float position;

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

	float distance = length(lightPos - FragPos);
	float attenuation = 1.0 / (constant + linea * distance + quadratic * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	vec3 result = ambient + diffuse + specular;
	//FragColor = texture(ourTexture, TexCoord);
	FragColor = vec4(result, 1.0);
	/*vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

	// diffuse 
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * texture(material.diffuse, TexCoords).rgb;

	// specular
	vec3 viewDir = normalize(viewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	// attenuation
	float distance = length(light.position - FragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;

	vec3 result = ambient + diffuse + specular;
	FragColor = vec4(result, 1.0);*/
};