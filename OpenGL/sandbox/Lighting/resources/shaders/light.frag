#version 450 core

in VS_OUT
{
	vec3 normal;
	vec2 texCoord;
	vec3 worldPos;
} fs_in;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

struct DirectionalLight
{
	vec3 lightColor;
	vec3 lightDir;
};

// struct PointLight
// {
// 	vec3 lightColor;
// 	vec3 lightPos;

// 	float constant;
// 	float linear;
// 	float quadratic;
// };

// struct SpotLight
// {
// 	vec3 lightColor;
// 	vec3 lightPos;
// 	vec3 direction;
// 	float cutOff;
// 	float outerCutoff;

// 	float constant;
// 	float linear;
// 	float quadratic;
// };

uniform vec3 u_ambient;
uniform vec3 u_cameraPos;
uniform Material u_material;

uniform DirectionalLight u_dirLight;
// #define NR_POINT_LIGHTS 4
// uniform PointLight pointLights[NR_POINT_LIGHTS];
// uniform SpotLight spotLight;

vec3 calcDirLight(DirectionalLight light, vec3 norm, vec3 viewDir)
{
	vec3 lightDir = normalize(light.lightDir);
	float NdotL = max(dot(norm, lightDir), 0.0);
	vec3 diff = NdotL * light.lightColor * texture(material.diffuse, fs_in.texCoord).rgb;

	vec3 h = normalize(viewDir + lightDir);
	float NdotH = max(dot(norm, h), 0.0);
	vec3 spec = pow(NdotH, material.shininess) * light.lightColor * texture(material.specular, fs_in.texCoord).rgb;

	return diff + spec;
}

// vec3 calcPointLight(PointLight light, vec3 norm, vec3 viewDir, vec3 fragPos)
// {
// 	vec3 lightDir = normalize(light.lightPos - fragPos);
// 	float NdotL = max(dot(norm, lightDir), 0.0);
// 	vec3 diff = NdotL * light.lightColor * texture(material.diffuse, fs_in.texCoord).rgb;

// 	vec3 h = normalize(viewDir + lightDir);
// 	float NdotH = max(dot(norm, h), 0.0);
// 	vec3 spec = pow(NdotH, material.shininess) * light.lightColor * texture(material.specular, fs_in.texCoord).rgb;

// 	float distance = length(light.lightPos - fragPos);
// 	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

// 	return (diff + spec) * attenuation;
// }

// vec3 calcSpotLight(SpotLight light, vec3 norm, vec3 viewDir, vec3 fragPos)
// {
// 	vec3 lightDir = normalize(light.lightPos - fragPos);
// 	float NdotL = max(dot(norm, lightDir), 0.0);
// 	vec3 diff = NdotL * light.lightColor * texture(material.diffuse, fs_in.texCoord).rgb;

// 	vec3 h = normalize(viewDir + lightDir);
// 	float NdotH = max(dot(norm, h), 0.0);
// 	vec3 spec = pow(NdotH, material.shininess) * light.lightColor * texture(material.specular, fs_in.texCoord).rgb;

// 	float theta = dot(lightDir, normalize(-light.direction));
// 	float epsilon = (light.cutOff - light.outerCutoff);
// 	float intensity = clamp((theta - light.outerCutoff) / epsilon, 0.0, 1.0);
// 	diff *= intensity;
// 	spec *= intensity;

// 	float distance = length(light.lightPos - fragPos);
// 	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * distance * distance);

// 	return (diff + spec) * attenuation;
// }

void main()
{
	vec3 norm = normalize(fs_in.normal);
	vec3 viewDir = normalize(cameraPos - fs_in.worldPos);

	vec3 col = calcDirLight(dirLight, norm, viewDir);
	// for(int i = 0; i < NR_POINT_LIGHTS; i++)
	// {
	// 	col += calcPointLight(pointLights[i], norm, viewDir, fs_in.worldPos);
	// }
	// col += calcSpotLight(spotLight, norm, viewDir, fs_in.worldPos);
	col += (ambient * texture(material.diffuse, fs_in.texCoord).rgb);
	gl_FragColor = vec4(col, 1.0);
}