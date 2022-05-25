#version 330 core
          
out vec4 FragColor;

in vec2 texCoord;
in vec3 outNormal;
in vec3 fragPos;

uniform sampler2D u_Texture;
uniform mat4 u_ViewProjection;
uniform vec3 u_ViewPos;
uniform vec3 u_SceneColour;

float ambientLightStrength = 0.2f;
float diffuseLightStrength = 0.6f;
float specularLightStrength = 0.5f;

vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
vec3 objectColor = vec3(0.5f, 1.0f, 0.5f);        
vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);

vec3 ambientLight = lightColor * ambientLightStrength;

// diffuse
vec3 norm = normalize(outNormal);
vec3 lightDir = normalize(lightPos - fragPos);
float diff = max(dot(norm, lightDir), 0.0);
vec3 diffuseLight = diff * lightColor * diffuseLightStrength;

// speculard
vec3 viewDir = normalize(u_ViewPos - fragPos);
vec3 reflectDir = reflect(-lightDir, norm);
float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
vec3 specularLight = specularLightStrength * spec * lightColor;


vec3 result = (ambientLight + diffuseLight + specularLight) * u_SceneColour;

void main()
{
     // FragColor = texture(u_Texture, texCoord);
        FragColor = vec4(result, 1.0f);
}