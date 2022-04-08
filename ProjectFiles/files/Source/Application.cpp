#include "Application.h"
#include <iostream>
#include <string>
#include <filesystem>


Application::Application()
{
    m_AppWindow = new Window(1280, 720, "App", NULL, NULL);
    m_WorldSettings.gravity = rp3d::Vector3(0, -9.81f, 0);
    m_PhysicsWorld = m_PhysicsCommon.createPhysicsWorld(m_WorldSettings);

}
Application::~Application()
{
    m_PhysicsCommon.destroyPhysicsWorld(m_PhysicsWorld);
    delete m_AppWindow;
}

void Application::Run()
{
    const double dt = 1.0 / 60.0;

    double currentTime = glfwGetTime();
    double accumulator = 0.0;

    std::string projectPath = std::filesystem::current_path().parent_path().string(); 
    std::string assetPath = projectPath + "\\Resources\\";
    std::string shaderPath = projectPath + "\\files\\" + "\\Shaders\\";

    std::string vertexShaderSrc = shaderPath + "default.vert";
    std::string fragmentShaderSrc = shaderPath + "default.frag";


    m_Renderer = std::make_unique<Renderer>();
    m_Texture = std::make_unique<Texture>(assetPath + "container.jpg");
    m_Shader = std::make_shared<Shader>(vertexShaderSrc, fragmentShaderSrc);

    m_MonkeyHead = std::make_shared<GameObject>(assetPath + "monkey.obj", "MonkeyHead_1", m_PhysicsWorld);
    m_Ground = std::make_shared<GameObject>(m_PhysicsWorld);

    rp3d::SphereShape* sphere = m_PhysicsCommon.createSphereShape(1.0f);
    rp3d::BoxShape* box = m_PhysicsCommon.createBoxShape(rp3d::Vector3(5.0f, 0.1f, 5.0f));


    m_MonkeyHead->SetPosition(rp3d::Vector3(0.0f, 5.0f, 0.0f));
    m_MonkeyHead->AddSphereShape(sphere);


    m_Ground->GenerateQuad();
    m_Ground->SetRotation(rp3d::Vector3(0.0f, 0.0f, 45.0f));
    m_Ground->SetPosition(rp3d::Vector3(0.0f, -5.0f, -5.0f));
    m_Ground->Properties.name = "Ground";
    m_Ground->AddBoxShape(box);


    while (!glfwWindowShouldClose(m_AppWindow->GetWindow()))
    {
        m_CameraInstance.RegisterKeyboardInput(m_AppWindow->GetWindow());
        m_CameraInstance.RegisterMouseInput(m_AppWindow->GetWindow());

      
        double newTime = glfwGetTime();
        double frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt) {
            m_PhysicsWorld->update(dt);
            accumulator -= dt;

        }

        m_Renderer->Setup();
        m_Renderer->Submit(m_MonkeyHead, m_Shader, m_CameraInstance);
        m_Renderer->Submit(m_Ground, m_Shader, m_CameraInstance);


        /* Swap front and back buffers */
        glfwSwapBuffers(m_AppWindow->GetWindow());

        /* Poll for and process events */
        glfwPollEvents();
    }
}


