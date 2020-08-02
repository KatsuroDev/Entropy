#type vertex
#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_Model;
uniform mat4 u_ViewProjection;

out vec3 v_Position;
out vec2 v_TexCoord;
out vec3 v_Normal;

void main()
{
	// Calculate the transformed vertex
	vec4 transformedModelPosition = u_Model * vec4(a_Position, 1.0);

	// Calculate the projected vertex
	gl_Position = u_ViewProjection * transformedModelPosition;

	// Calculate the transformed normal                      w = 0!
	vec4 transformedModelNormal = normalize(u_Model * vec4(a_Normal, 0.0));

	v_Position = transformedModelPosition.xyz;
	v_TexCoord = a_TexCoord;

	// TODO: compute this on cpu and pass as uniform (costly)
	v_Normal = mat3(transpose(inverse(u_Model))) * a_Normal;
}

#type fragment
#version 330 core

uniform vec3 u_CameraPosition;

in vec3 v_Position;
in vec2 v_TexCoord;
in vec3 v_Normal;

struct DirectionalLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

struct Light
{
    vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Light u_Light;

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
    float shininess;
};

uniform Material u_Material;

vec3 CalculateDirectionLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	// combine results
    vec3 ambient  = light.ambient  * vec3(texture(u_Material.diffuse, v_TexCoord));
	vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_Material.diffuse, v_TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_TexCoord));
    return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    // diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
    // attenuation
    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
  			     light.quadratic * (distance * distance));
    // combine results
    vec3 ambient  = light.ambient  * vec3(texture(u_Material.diffuse, v_TexCoord));
    vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_Material.diffuse, v_TexCoord));
    vec3 specular = light.specular * spec * vec3(texture(u_Material.specular, v_TexCoord));
    return (ambient + diffuse + specular) * attenuation;
}

layout(location = 0) out vec4 color;

void main()
{
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(u_CameraPosition - v_Position);
	vec3 lightDir = normalize(u_Light.position - v_Position);
	vec3 reflectDir = reflect(-lightDir, norm);

	// Calculate the distance from the light source
	float distance = length(u_Light.position - v_Position);
	float attenuation = 1.0 / (u_Light.constant + u_Light.linear * distance +
    		    u_Light.quadratic * (distance * distance));

	// ambient
	vec3 ambient = u_Light.ambient * vec3(texture(u_Material.diffuse, v_TexCoord));

	// diffuse
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = u_Light.diffuse * diff * vec3(texture(u_Material.diffuse, v_TexCoord));

	// specular
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	vec3 specular = u_Light.specular * spec * vec3(texture(u_Material.specular, v_TexCoord));

	vec3 result = (ambient + diffuse + specular) * attenuation;
	color = vec4(result, 1.0);
}
