 #version 330 core    
 
layout (location = 0) in vec3 a_position;

out vec4 particleColor;
out float lifetime;

uniform mat4 u_viewProjection;
uniform vec4 u_color;
uniform float u_lifeTime;

void main()
{
	float scale = 10.0f;

	particleColor = u_color;
	lifetime = u_lifeTime;

    gl_Position = u_viewProjection * vec4(a_position * scale, 1.0f);
  
}