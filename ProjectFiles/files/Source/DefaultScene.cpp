#include "DefaultScene.h"

DefaultScene::DefaultScene()
{
}

DefaultScene::~DefaultScene()
{
}

void DefaultScene::Begin(ObjectManager& objectManager, const Component& componentData)
{
    GameObject& monkeyHead = objectManager.CreateGameObject();
    monkeyHead.name = "Monkey Head";
    monkeyHead.AddComponent<MeshRenderer>(componentData);
    monkeyHead.AddComponent<Rigidbody>(componentData);
    auto& monkeyHeadRB = monkeyHead.GetComponent<Rigidbody>();
    auto& monkeyHeadMesh = monkeyHead.GetComponent<MeshRenderer>();
    monkeyHeadMesh.LoadFromOBJ(EnginePaths::AssetPath() + "monkey.obj");
    monkeyHeadRB.AddSphereCollider(1.0f);
    monkeyHeadRB.SetPhysicalMaterialProperties(0.5f, 0.5f);
    monkeyHeadRB.SetPosition(rp3d::Vector3(0.0f, 5.0f, 0.0f));
    monkeyHeadRB.SetRigidbodyType(rp3d::BodyType::STATIC);



    GameObject& terrain = objectManager.CreateGameObject();
    terrain.name = "Terrain";
    terrain.AddComponent<MeshRenderer>(componentData);
    terrain.AddComponent<Rigidbody>(componentData);
    auto& terrainRB = terrain.GetComponent<Rigidbody>();
    auto& terrainMesh = terrain.GetComponent<MeshRenderer>();
    terrainMesh.LoadFromOBJ(EnginePaths::AssetPath() + "terrain.obj");
    terrainRB.SetRigidbodyType(rp3d::BodyType::STATIC);
    terrainRB.SetPosition(rp3d::Vector3(0.0f, -10.0f, 0.0f));
    // terrainMesh.LoadFromHeightMap(assetPath + "terrain.png");
    // terrainRB.SetRotation(rp3d::Vector3(0.0f, 90.0f, 0.0f));
    // terrainRB.AddConcaveColldier(terrainMesh.GetRawVertices(), terrainMesh.GetRawNormals(), terrainMesh.GetIndices());


    GameObject& particleSystem = objectManager.CreateGameObject();
    particleSystem.name = "Particle System";
    particleSystem.AddComponent<ParticleSystem>(componentData, 100, ParticleDirection::DOWN);


    std::string particleVertexShaderSrc = EnginePaths::ShaderPath() + "particle.vert";
    std::string particleFragmentShaderSrc = EnginePaths::ShaderPath() + "particle.frag";
    m_particleShader = std::make_shared<Shader>(particleVertexShaderSrc, particleFragmentShaderSrc);


    /*
      rp3d::Vector3 colldierSize(5.0f, 0.2f, 5.0f);
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
      groundRB.SetPhysicalMaterialProperties(0.5f, 0.5f);
    */


}

void DefaultScene::Update(const float dt, ObjectManager& objectManager)
{
    for (auto& ref : objectManager.objectRegistry)
    {
        auto& retreivedObject = *ref.second;

        if (retreivedObject.HasComponent<ParticleSystem>())
        {
            auto& particleSystem = retreivedObject.GetComponent<ParticleSystem>();
            particleSystem.Update(dt);
        }
    }
}

void DefaultScene::Render(const std::unique_ptr<Renderer>& renderer, const std::shared_ptr<Shader> shader, Camera& camera, ObjectManager& objectManager)
{
    for (auto& ref : objectManager.objectRegistry)
    {
        auto& retreivedObject = *ref.second;
        
        if (retreivedObject.HasComponent<Rigidbody>() && retreivedObject.HasComponent<MeshRenderer>())
        {
            auto& rigidbody = retreivedObject.GetComponent<Rigidbody>();
            auto& meshRenderer = retreivedObject.GetComponent<MeshRenderer>();
            renderer->Submit(rigidbody.GetOpenGLTransform(), meshRenderer.GetVertexArray(), meshRenderer.GetIndexBuffer(), shader, camera);
        }

        if (retreivedObject.HasComponent<ParticleSystem>())
        {
            m_particleShader->UploadUniformMat4("u_projection", camera.GetProjectionMatrix());
            m_particleShader->UploadUniformMat4("u_viewMatrix", camera.GetViewMatrix());
            auto& particleSystem = retreivedObject.GetComponent<ParticleSystem>();
            particleSystem.Render(m_particleShader);
        }
    }
}
