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
    Component componentData(m_PhysicsWorld, &m_PhysicsCommon);

    m_MonkeyHead = std::make_shared<GameObject>(assetPath + "monkey.obj");
    m_MonkeyHead->AddComponent<Rigidbody>(componentData);
    auto& m_MonkeyHeadRB = m_MonkeyHead->GetComponent<Rigidbody>();
    m_MonkeyHeadRB.AddSphereCollider(1.0f);
    m_MonkeyHeadRB.SetPhysicalMaterialProperties(1.0f, 1.0f);


    m_Ground = std::make_shared<GameObject>();
    m_Ground->GenerateQuad();
    m_Ground->AddComponent<Rigidbody>(componentData);
    rp3d::Vector3 colldierSize(5.0f, 0.2f, 5.0f);
    auto& groundRB = m_Ground->GetComponent<Rigidbody>();
    groundRB.SetRigidbodyType(rp3d::BodyType::STATIC);
    groundRB.SetPositon(rp3d::Vector3(0.0f, -10.0f, -5.0f));
    groundRB.SetRotation(rp3d::Vector3(0.0f, 0.0f, 45.0f));
    groundRB.AddBoxCollider(colldierSize);
    groundRB.SetPhysicalMaterialProperties(0.0f, 0.0f);

    while (!glfwWindowShouldClose(m_AppWindow->GetWindow()))
    {
        m_CameraInstance.RegisterKeyboardInput(m_AppWindow->GetWindow());
        m_CameraInstance.RegisterMouseInput(m_AppWindow->GetWindow());

      
        double newTime = glfwGetTime();
        double frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt) 
        {
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


