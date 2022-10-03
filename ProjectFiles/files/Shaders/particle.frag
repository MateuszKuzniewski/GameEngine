#version 330 core
          
out vec4 FragColor;

in vec4 particleColor;
in float lifetime;

void main()
{
    FragColor = particleColor;
}