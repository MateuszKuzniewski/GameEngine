#include "Application.h"
#include <iostream>
#include <string>
#include <filesystem>


Application::Application()
{
    m_AppWindow = new Window(1920, 1080, "App", NULL, NULL);
    m_WorldSettings.gravity = rp3d::Vector3(0, -9.81f, 0);
    m_PhysicsWorld = m_PhysicsCommon.createPhysicsWorld(m_WorldSettings);

}
Application::~Application()
{
    m_PhysicsCommon.destroyPhysicsWorld(m_PhysicsWorld);

    delete m_AppWindow;
}

void Application::Initialize()
{
    // Components
    componentData = Component(m_PhysicsWorld, &m_PhysicsCommon);


    // Shader
    std::string vertexShaderSrc = EnginePaths::ShaderPath() + "default.vert";
    std::string fragmentShaderSrc = EnginePaths::ShaderPath() + "default.frag";
    m_Shader = std::make_shared<Shader>(vertexShaderSrc, fragmentShaderSrc);

    std::string particleVertexShaderSrc = EnginePaths::ShaderPath() + "particle.vert";
    std::string particleFragmentShaderSrc = EnginePaths::ShaderPath() + "particle.frag";
    m_particleShader = std::make_shared<Shader>(particleVertexShaderSrc, particleFragmentShaderSrc);


    // Textures
    m_Texture = std::make_unique<Texture>(EnginePaths::AssetPath() + "container.jpg");


    // Systems
    m_Renderer = std::make_unique<Renderer>();
    m_GUI = std::make_unique<GUI>(m_AppWindow);
    m_Input = std::make_unique<Input>(m_AppWindow);


    // Scenes
    m_Scene = std::make_unique<Scene>();
    m_DefaultScene = std::make_unique<DefaultScene>();
    m_ParticleScene = std::make_unique<ParticleSystemScene>();
}


void Application::Run()
{
    float sceneColour[4] = { 0.5f, 1.0f, 0.5f, 1.0f };
    
    const double dt = 1.0 / 60.0;
    double currentTime = glfwGetTime();
    double accumulator = 0.0;

    Initialize();

    //m_DefaultScene->Begin(m_ObjectManager, componentData);
    m_ParticleScene->Begin(m_ObjectManager, componentData);

    // Change default scene to load a new scene
    m_Scene = std::move(m_ParticleScene);


    while (!glfwWindowShouldClose(m_AppWindow->GetWindow()))
    {
        m_Input->RegisterKeyboardEvents();
        m_Input->RegisterMouseEvents();
        double newTime = glfwGetTime();
        double frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= dt) 
        {
            m_PhysicsWorld->update(dt);
            m_Scene->Update(dt);
            accumulator -= dt;
           
        }
        
        m_Shader->UploadUniformVec3("u_sceneColour", glm::vec3(sceneColour[0], sceneColour[1], sceneColour[2]));
        m_Renderer->Setup();
        m_Scene->Render(m_Renderer, m_particleShader, m_CameraInstance, m_ObjectManager);
    
        m_GUI->Render();
      
        glfwSwapBuffers(m_AppWindow->GetWindow());
        glfwPollEvents();
    }
}



