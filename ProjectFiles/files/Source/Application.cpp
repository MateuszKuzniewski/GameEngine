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
    std::string shaderPath = projectPath + "\\files\\" + "\\Shaders\\";

    std::string vertexShaderSrc = shaderPath + "basic.vert";
    std::string fragmentShaderSrc = shaderPath + "basic.frag";

    m_PhysicsWorld = std::make_unique<PhysicsWorld>();
    m_Renderer = std::make_unique<Renderer>();

    
    m_MonkeyHead = std::make_shared<GameObject>(assetPath + "monkey.obj", "MonkeyHead_1");
    m_MonkeyHead->Transform.position = glm::vec3(0.0f, 5.0f, 0.0f);
    m_MonkeyHead->Properties.Gravity = true;

 /*   m_MonkeyHead2 = std::make_shared<GameObject>(assetPath + "monkey.obj", "MonkeyHead_2");
    m_MonkeyHead2->SetPosition(-2.0f, 0.0f, 0.0f);
    m_MonkeyHead2->Properties.Gravity = true;*/

    m_Ground = std::make_shared<GameObject>();
    m_Ground->SetName("Ground");
    m_Ground->GenerateQuad();
    m_Ground->Transform.position = glm::vec3(0.0f, -5.0f, -5.0f);
    m_Ground->Properties.Gravity = false;


    m_Ground2 = std::make_shared<GameObject>();
    m_Ground2->SetName("Ground_2");
    m_Ground2->GenerateQuad();
    m_Ground2->Transform.position = glm::vec3(0.0f, 7.0f, -5.0f);
    m_Ground2->Properties.Gravity = false;


    // Texture
    m_Texture = std::make_unique<Texture>(assetPath + "container.jpg");

   
    // Shaders 
    m_Shader = std::make_shared<Shader>(vertexShaderSrc, fragmentShaderSrc);

    m_PhysicsWorld->Add(m_MonkeyHead);
    //m_PhysicsWorld->Add(m_MonkeyHead2);
    m_PhysicsWorld->Add(m_Ground);
    m_PhysicsWorld->Add(m_Ground2);

    while (!glfwWindowShouldClose(m_AppWindow->GetWindow()))
    {
        m_CameraInstance.RegisterKeyboardInput(m_AppWindow->GetWindow());
        m_CameraInstance.RegisterMouseInput(m_AppWindow->GetWindow());


        m_Renderer->Setup();
        m_Renderer->Submit(m_MonkeyHead, m_Shader, m_CameraInstance);
        //m_Renderer->Submit(m_MonkeyHead2, m_Shader, m_CameraInstance);
        m_Renderer->Submit(m_Ground, m_Shader, m_CameraInstance);
        m_Renderer->Submit(m_Ground2, m_Shader, m_CameraInstance);


        m_PhysicsWorld->Update();

        /* Swap front and back buffers */
        glfwSwapBuffers(m_AppWindow->GetWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }
}