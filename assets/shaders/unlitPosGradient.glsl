#type vertex
#version 330 core
			
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextCoord;
layout(location = 2) in vec3 a_Normal;

uniform mat4 u_Transform;
uniform mat4 u_ViewProjection;

out vec3 u_Color;

void main()
{
	// Calculate the projected vertex
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position.xyz, 1.0);

	float diffuse = dot(a_Normal, vec3(0.0, 1.0, 0.0));

	u_Color = vec3(diffuse, diffuse, diffuse);
}

#type fragment
#version 330 core
			
layout(location = 0) out vec4 color;

in vec3 u_Color;

void main()
{
	color = vec4(u_Color, 1.0);
}
