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
    m_Texture  = std::make_unique<Texture>(assetPath + "container.jpg");
    m_Shader   = std::make_shared<Shader>(vertexShaderSrc, fragmentShaderSrc);
    m_GUI      = std::make_unique<GUI>(m_AppWindow);
    m_Input    = std::make_unique<Input>(m_AppWindow);
    Component componentData(m_PhysicsWorld, &m_PhysicsCommon);

    m_MonkeyHead = std::make_shared<GameObject>();
    m_MonkeyHead->AddComponent<MeshRenderer>(componentData);
    m_MonkeyHead->AddComponent<Rigidbody>(componentData);
    auto& monkeyHeadRB = m_MonkeyHead->GetComponent<Rigidbody>();
    auto& monkeyHeadMesh = m_MonkeyHead->GetComponent<MeshRenderer>();
    monkeyHeadMesh.LoadFromOBJ(assetPath + "monkey.obj");
    monkeyHeadRB.AddSphereCollider(1.0f);
    monkeyHeadRB.SetPhysicalMaterialProperties(0.5f, 0.5f);
    monkeyHeadRB.SetPosition(rp3d::Vector3(0.0f, 10.0f, 0.0f));

    

  /*  rp3d::Vector3 colldierSize(5.0f, 0.2f, 5.0f);
    m_Ground = std::make_shared<GameObject>();
    m_Ground->AddComponent<MeshRenderer>(componentData);
    m_Ground->AddComponent<Rigidbody>(componentData);
    auto& groundRB = m_Ground->GetComponent<Rigidbody>();
    auto& groundMesh = m_Ground->GetComponent<MeshRenderer>();
    groundMesh.GenerateQuad();
    groundRB.SetRigidbodyType(rp3d::BodyType::STATIC);
    groundRB.SetPositon(rp3d::Vector3(0.0f, -10.0f, -5.0f));
    groundRB.SetRotation(rp3d::Vector3(0.0f, 0.0f, 45.0f));
    groundRB.AddBoxCollider(colldierSize);
    groundRB.SetPhysicalMaterialProperties(0.5f, 0.5f);*/

    m_Terrain = std::make_shared<GameObject>();
    m_Terrain->AddComponent<MeshRenderer>(componentData);
    m_Terrain->AddComponent<Rigidbody>(componentData);
    auto& terrainRB = m_Terrain->GetComponent<Rigidbody>();
    auto& terrainMesh = m_Terrain->GetComponent<MeshRenderer>();
    //terrainMesh.LoadFromHeightMap(assetPath + "terrain.png");
    terrainMesh.LoadFromOBJ(assetPath + "terrain.obj");
    terrainRB.SetRigidbodyType(rp3d::BodyType::STATIC);
    terrainRB.SetPosition(rp3d::Vector3(0.0f, -10.0f, 0.0f));
    terrainRB.AddConcaveColldier(terrainMesh.GetRawVertices(), terrainMesh.GetRawNormals(), terrainMesh.GetIndices());



    float sceneColour[4] = { 0.5f, 1.0f, 0.5f, 1.0f };


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
            accumulator -= dt;
           
        }
        

        m_Shader->UploadUniformVec3("u_SceneColour", glm::vec3(sceneColour[0], sceneColour[1], sceneColour[2]));
        m_Renderer->Setup();
        m_Renderer->Submit(monkeyHeadRB.GetOpenGLTransform(), monkeyHeadMesh.GetVertexArray(), monkeyHeadMesh.GetIndexBuffer(), m_Shader, m_CameraInstance);
        m_Renderer->Submit(terrainRB.GetOpenGLTransform(), terrainMesh.GetVertexArray(), terrainMesh.GetIndexBuffer(), m_Shader, m_CameraInstance);
        //m_Renderer->Submit(groundRB.GetOpenGLTransform(), groundMesh.GetVertexArray(), groundMesh.GetIndexBuffer(), m_Shader, m_CameraInstance);

        m_GUI->PrepareRender();
        m_GUI->Render();
      
        /* Swap front and back buffers */
        glfwSwapBuffers(m_AppWindow->GetWindow());
        /* Poll for and process events */
        glfwPollEvents();
    }


}


