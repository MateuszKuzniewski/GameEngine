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

    std::string currentPath = std::filesystem::current_path().parent_path().string(); 
    std::string assetPath = currentPath + "\\Resources\\container.jpg";

    std::string vertexShaderSrc = R"(
        #version 330 core    
 
        layout (location = 0) in vec3 a_Position;
        layout (location = 1) in vec2 a_TexCoord; 
        // layout (location = 2) in vec3 a_Color;

       // out vec3 outColor;
        out vec2 texCoord;
        uniform mat4 u_ViewProjection;

        void main()
        {
            gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            // outColor = a_Color;
            texCoord = a_TexCoord;
        }
    )";


    std::string fragmentShaderSrc = R"(
        #version 330 core
          
        out vec4 FragColor;
       // in vec3 outColor;
        in vec2 texCoord;
      
        uniform sampler2D u_Texture;

        void main()
        {
              FragColor = texture(u_Texture, texCoord);
        }
    )";



    float vertices[] = {

        // Coordinates x,y,z   // Textures
        0.5f,  0.5f,  0.5f,    1.0f, 1.0f,//0
       -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,//1
       -0.5f,  0.5f, -0.5f,    0.0f, 0.0f,//2
        0.5f,  0.5f, -0.5f,    0.0f, 1.0f,//3
        0.5f, -0.5f,  0.5f,    1.0f, 1.0f,////4
       -0.5f, -0.5f,  0.5f,    1.0f, 0.0f,////5
       -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,////6
        0.5f, -0.5f, -0.5f,    0.0f, 1.0f////7
    };

    uint32_t indecies[] = {

        0, 1, 3, //top 1
        3, 1, 2, //top 2
        2, 6, 7, //front 1
        7, 3, 2, //front 2
        7, 6, 5, //bottom 1
        5, 4, 7, //bottom 2
        5, 1, 4, //back 1
        4, 1, 0, //back 2
        4, 3, 7, //right 1
        3, 4, 0, //right 2
        5, 6, 2, //left 1
        5, 1, 2  //left 2
    };


    // Create Vertex Array
    m_VertexArray = std::make_shared<VertexArray>();

    // Vertex buffer object
    m_VertexBuffer = std::make_shared<VertexBuffer>(vertices, sizeof(vertices));
    
    // Create layout
    BufferLayout layout = {
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float2, "a_TexCoord"}, 
       // { ShaderDataType::Float3, "a_Color" }
        
    };

    m_VertexBuffer->SetLayout(layout);
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    


    // Index buffer object
    m_IndexBuffer = std::make_shared<IndexBuffer>(indecies, sizeof(indecies) / sizeof(uint32_t));
    m_VertexArray->AddIndexBuffer(m_IndexBuffer);


    // Texture
    m_Texture = std::make_unique<Texture>(assetPath);

   
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

        m_VertexArray->Bind();
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);



        /* Swap front and back buffers */
        glfwSwapBuffers(m_AppWindow->GetWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }
}