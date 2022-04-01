 #version 330 core    
 
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal; 
layout (location = 2) in vec2 a_TexCoord; 


out vec2 texCoord;
out vec3 outNormal;
out vec3 fragPos;

uniform mat4 u_ViewProjection;
uniform mat4 u_ViewMatrix;
uniform mat4 u_Transform;

void main()
{
    texCoord = a_TexCoord;
    outNormal = a_Normal;


    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
    fragPos = vec3(u_ViewMatrix * u_Transform * vec4(a_Position, 1.0));
}