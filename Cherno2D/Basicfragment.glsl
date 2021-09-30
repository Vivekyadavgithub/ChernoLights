layout(location = 0) out vec4 FragColor;
struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}; 
  
uniform Material material;

struct Light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;

uniform vec3 lightPos[10];

uniform vec3 viewPos;
uniform vec3 lightColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoord;
vec3 textureSpecular = {0.5f, 0.5f, 0.5f};
float texShine = 64.0f;
float constant = 1.0f;
float linea = 0.09f;
float quadratic = 0.032f;


vec3 CalcPointLight(vec3 lightPos, vec3 norm, vec3 FragPos ,vec3 viewDir){
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoord));
    
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);

    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoord)); 
    
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoord));  
    
	float distance = length(lightPos - FragPos);
	float attenuation = 1.0 / (constant + linea * distance + quadratic * (distance * distance));
	 
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
    return ambient + diffuse + specular;
}
void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    vec3 result = {0, 0, 0};
    for(int i = 0; i < 10; i++)
        result += CalcPointLight(lightPos[i], norm, FragPos, viewDir);
    FragColor = vec4(result, 1.0);
	
};