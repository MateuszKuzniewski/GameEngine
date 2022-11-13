#version 330 core
          
out vec4 FragColor;

uniform vec4 u_particleColor;
uniform float u_lifetime;

void main()
{
    FragColor = vec4(u_particleColor.x, u_particleColor.y, u_particleColor.z, u_lifetime);
}