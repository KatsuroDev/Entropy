#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_MaterialDiffuseColor;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec3 u_MaterialDiffuseColor;

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

	u_MaterialDiffuseColor = a_MaterialDiffuseColor;

	v_Position = vec3(transformedModelPosition.xyz);
	v_Normal = vec3(transformedModelNormal.xyz);
}

#type fragment
#version 330 core
			
layout(location = 0) out vec4 color;

uniform vec3 u_AmbiantLight;
uniform vec3 u_PointLightPosition;
uniform vec3 u_PointLight;
uniform vec3 u_CameraPosition;

in vec3 u_MaterialDiffuseColor;
in vec3 v_Position;
in vec3 v_Normal;

void main()
{
	// Calculate the distance from the light source
	float pointLightDistance = length(u_PointLightPosition - v_Position);

	// Calculate the vector from the vertex position to the eye
	vec3 vertexToEyeVector = normalize(u_CameraPosition - v_Position);

	// Calculate the vector from the vertex to the light position
	vec3 vertexToLightVector = normalize(u_PointLightPosition - v_Position);
	
	// Calculate the reflected light vector from the surface normal
	vec3 reflectedLightVector = reflect(-vertexToLightVector, v_Normal);

	// Calculate the amount of specular light coming to the eye
	float specularity = pow(clamp(dot(reflectedLightVector, vertexToEyeVector), 0.0, 1.0), 64.0);

	// Calculate the diffusion factor for the vertex
	float diffusibility = clamp(dot(v_Normal, vertexToLightVector), 0.0, 1.0);

	vec3 specularLight = vec3(specularity, specularity, specularity) * u_PointLight;
	vec3 diffuseLight = vec3(diffusibility, diffusibility, diffusibility) * u_PointLight;

	color = vec4(u_AmbiantLight + specularLight + (diffuseLight * u_MaterialDiffuseColor) / (pointLightDistance * pointLightDistance), 1.0);
}
