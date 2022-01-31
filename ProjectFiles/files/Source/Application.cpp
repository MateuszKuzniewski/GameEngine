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
        layout (location = 1) in vec2 a_TexCoord; 


        out vec2 texCoord;
        out vec3 outNormal;
        out vec3 fragPos;

        uniform mat4 u_ViewProjection;
        uniform mat4 u_ViewMatrix;

        void main()
        {
            texCoord = a_TexCoord;
            outNormal = a_Normal;


            gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            fragPos = vec3(u_ViewMatrix * vec4(a_Position, 1.0));
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
        
        float ambientLightStrength = 0.2f;
        float diffuseLightStrength = 0.6f;

        vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
        vec3 objectColor = vec3(0.5f, 1.0f, 0.5f);        
        vec3 lightPos = vec3(1.2f, 1.0f, 2.0f);

        vec3 ambientLight = lightColor * ambientLightStrength;


        vec3 norm = normalize(outNormal);
        vec3 lightDir = normalize(lightPos - fragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        
        vec3 diffuseLight = diff * lightColor * diffuseLightStrength;
        vec3 result = (ambientLight + diffuseLight) * objectColor;

        void main()
        {
             // FragColor = texture(u_Texture, texCoord);
                FragColor = vec4(result, 1.0f);
        }
    )";

    m_Model = std::make_unique<ModelMesh>(assetPath + "monkey.obj");
    

    // Create Vertex Array
    m_VertexArray = std::make_shared<VertexArray>();

    // Vertex buffer object
    m_VertexBuffer = std::make_shared<VertexBuffer>(&m_Model->GetVertices()[0], m_Model->GetVertices().size() * sizeof(*m_Model->GetVertices().data()));
    
    // Create layout
    BufferLayout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float3, "a_Normal"   }
       // { ShaderDataType::Float2, "a_TexCoord"}, 
       // { ShaderDataType::Float3, "a_Color" }
        
    };

    // Vertex Array Object
    m_VertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    


    // Index Buffer Object
    m_IndexBuffer = std::make_shared<IndexBuffer>(&m_Model->GetIndecies()[0], m_Model->GetIndecies().size());
    m_VertexArray->AddIndexBuffer(m_IndexBuffer);


    // Texture
    m_Texture = std::make_unique<Texture>(assetPath + "container.jpg");

   
    // Shaders 
    m_Shader = std::make_shared<Shader>(vertexShaderSrc, fragmentShaderSrc);

    std::cout << "Number of vertex arrays created: "  << m_VertexArray.use_count()  << std::endl;
    std::cout << "Number of vertex buffers created: " << m_VertexBuffer.use_count() << std::endl;
    std::cout << "Number of index buffers created: "  << m_IndexBuffer.use_count()  << std::endl;

    glEnable(GL_DEPTH_TEST);




    while (!glfwWindowShouldClose(m_AppWindow->GetWindow()))
    {
        m_CameraInstance.RegisterKeyboardInput(m_AppWindow->GetWindow());
        m_CameraInstance.RegisterMouseInput(m_AppWindow->GetWindow());

        glClearColor(0.1f, 0.1, 0.1f, 0.1f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /* Render here */

        m_Shader->Bind();
        m_Shader->UploadUniformMat4("u_ViewProjection", m_CameraInstance.GetViewProjectionMatrix());
        m_Shader->UploadUniformMat4("u_ViewMatrix", m_CameraInstance.GetViewMatrix());

        m_VertexArray->Bind();
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);
        //glDrawArrays(GL_TRIANGLES, 0, m_Model->GetIndecies().size());


        /* Swap front and back buffers */
        glfwSwapBuffers(m_AppWindow->GetWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }
}