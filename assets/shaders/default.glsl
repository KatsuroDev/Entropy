#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec3 u_MaterialColor;
out vec3 v_Position;
out vec3 v_Normal;

void main()
{
	// Calculate the transformed vertex
	vec4 transformedModelPosition = u_Transform * vec4(a_Position.xyz, 1.0);

	// Calculate the projected vertex
	gl_Position = u_ViewProjection * transformedModelPosition;

	// Calculate the transformed normal                      w = 0!
	vec4 transformedModelNormal = normalize(u_Transform * vec4(a_Normal, 0.0));

	u_MaterialColor = vec3(1.0, 1.0, 1.0);

	v_Position = vec3(transformedModelPosition.xyz);
	v_Normal = vec3(transformedModelNormal.xyz);
}

#type fragment
#version 330 core
			
layout(location = 0) out vec4 color;

uniform vec3 u_CameraPosition;

uniform float u_ShineDamper;
uniform float u_Reflectivity;

in vec3 u_MaterialColor;
in vec3 v_Position;
in vec3 v_Normal;

struct Light
{
    vec3 position;
    vec3 color;
	
    float constant;
    float linear;
    float quadratic;
};

uniform Light u_Light;

void main()
{

	// Calculate the distance from the light source
	// TOOD: take frag position
	float distance = length(u_Light.position - v_Position);
	float attenuation = 1.0 / (u_Light.constant + u_Light.linear * distance + 
    		    u_Light.quadratic * (distance * distance));

	// Calculate the vector from the vertex position to the eye
	vec3 vertexToEyeVector = normalize(u_CameraPosition - v_Position);

	// Calculate the vector from the vertex to the light position
	vec3 vertexToLightVector = normalize(u_Light.position - v_Position);
	
	// Calculate the reflected light vector from the surface normal
	vec3 reflectedLightVector = reflect(-vertexToLightVector, v_Normal);

	vec3 diffuse = u_Light.color * clamp(dot(v_Normal, vertexToLightVector), 0.0, 1.0);
	vec3 specular = u_Light.color * pow(clamp(dot(reflectedLightVector, vertexToEyeVector), 0.0, 1.0), u_ShineDamper) * u_Reflectivity;
	vec3 ambient = u_Light.color * 0.05; // TODO: change that

	color = vec4(((diffuse + ambient) * u_MaterialColor + specular) * attenuation, 1.0);
}
