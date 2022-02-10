#include "Application.h"
#include <iostream>
#include <string>
#include <filesystem>

Application::Application()
{
    m_AppWindow = new Window(1280, 720, "App", NULL, NULL);

    
}
Application::~Application()
{
    delete m_AppWindow;
}

void Application::Run()
{

    std::string projectPath = std::filesystem::current_path().parent_path().string(); 
    std::string assetPath = projectPath + "\\Resources\\";

    std::string vertexShaderSrc = R"(
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
    )";


    std::string fragmentShaderSrc = R"(
        #version 330 core
          
        out vec4 FragColor;

        in vec2 texCoord;
        in vec3 outNormal;
        in vec3 fragPos;

        uniform sampler2D u_Texture;
        uniform mat4 u_ViewProjection;
        uniform vec3 u_ViewPos;

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
        
        // specular
        vec3 viewDir = normalize(u_ViewPos - fragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
        vec3 specularLight = specularLightStrength * spec * lightColor;

        vec3 result = (ambientLight + diffuseLight + specularLight) * objectColor;

        void main()
        {
             // FragColor = texture(u_Texture, texCoord);
                FragColor = vec4(result, 1.0f);
        }
    )";

    
    m_MonkeyHead = std::make_shared<GameObject>();
    m_MonkeyHead->LoadModel(assetPath + "monkey.obj");
    m_MonkeyHead->SetPosition(0.0f, 3.0f, 0.0f);

    m_MonkeyHead2 = std::make_shared<GameObject>();
    m_MonkeyHead2->LoadModel(assetPath + "monkey.obj");
    m_MonkeyHead2->SetPosition(3.0f, 0.0f, 0.0f);

    m_Ground = std::make_shared<GameObject>();
    m_Ground->GenerateQuad();
    m_Ground->SetPosition(0.0f, -2.0f, -2.0f);
    

    // Texture
    m_Texture = std::make_unique<Texture>(assetPath + "container.jpg");

   
    // Shaders 
    m_Shader = std::make_shared<Shader>(vertexShaderSrc, fragmentShaderSrc);



    while (!glfwWindowShouldClose(m_AppWindow->GetWindow()))
    {
        m_CameraInstance.RegisterKeyboardInput(m_AppWindow->GetWindow());
        m_CameraInstance.RegisterMouseInput(m_AppWindow->GetWindow());


        m_Renderer->Setup();
        m_Renderer->Submit(m_MonkeyHead, m_Shader, m_CameraInstance);
        m_Renderer->Submit(m_MonkeyHead2, m_Shader, m_CameraInstance);
        m_Renderer->Submit(m_Ground, m_Shader, m_CameraInstance);
      


        /* Swap front and back buffers */
        glfwSwapBuffers(m_AppWindow->GetWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }
}