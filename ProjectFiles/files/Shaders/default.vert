 #version 330 core    
 
layout (location = 0) in vec3 a_position;
layout (location = 1) in vec3 a_normal; 
layout (location = 2) in vec2 a_texCoord; 


out vec2 texCoord;
out vec3 outNormal;
out vec3 fragPos;

uniform mat4 u_viewProjection;
uniform mat4 u_viewMatrix;
uniform mat4 u_transform;

void main()
{
    texCoord = a_texCoord;
    outNormal = a_normal;


    gl_Position = u_viewProjection * u_transform * vec4(a_position, 1.0);
    fragPos = vec3(u_viewMatrix * u_transform * vec4(a_position, 1.0));
}