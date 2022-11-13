 #version 330 core    
layout (location = 0) in vec3 a_Position;

uniform mat4 u_projection;
uniform mat4 u_transform;
uniform mat4 u_viewMatrix;


void main()
{
	mat4 modelView = u_viewMatrix;

	modelView[0][0] = 1.0f;
	modelView[0][1] = 0.0f;
	modelView[0][2] = 0.0f;

	modelView[1][0] = 0.0f;
	modelView[1][1] = 1.0f;
	modelView[1][2] = 0.0f;

	modelView[2][0] = 0.0f;
	modelView[2][1] = 0.0f;
	modelView[2][2] = 1.0f;
	
	gl_Position = u_projection * modelView * u_transform * vec4(a_Position, 1.0);
}