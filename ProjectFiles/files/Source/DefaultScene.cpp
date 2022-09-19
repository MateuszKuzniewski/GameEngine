#include "DefaultScene.h"

DefaultScene::DefaultScene()
{
}

DefaultScene::~DefaultScene()
{
}

void DefaultScene::Begin(ObjectManager& objectManager, const Component& componentData)
{
    GameObject& m_MonkeyHead = objectManager.CreateGameObject();
    m_MonkeyHead.name = "Monkey Head";
    m_MonkeyHead.AddComponent<MeshRenderer>(componentData);
    m_MonkeyHead.AddComponent<Rigidbody>(componentData);
    auto& monkeyHeadRB = m_MonkeyHead.GetComponent<Rigidbody>();
    auto& monkeyHeadMesh = m_MonkeyHead.GetComponent<MeshRenderer>();
    monkeyHeadMesh.LoadFromOBJ(EnginePaths::AssetPath() + "monkey.obj");
    monkeyHeadRB.AddSphereCollider(1.0f);
    monkeyHeadRB.SetPhysicalMaterialProperties(0.5f, 0.5f);
    monkeyHeadRB.SetPosition(rp3d::Vector3(0.0f, 5.0f, 0.0f));
    monkeyHeadRB.SetRigidbodyType(rp3d::BodyType::STATIC);



    GameObject& m_Terrain = objectManager.CreateGameObject();
    m_Terrain.name = "Terrain";
    m_Terrain.AddComponent<MeshRenderer>(componentData);
    m_Terrain.AddComponent<Rigidbody>(componentData);
    auto& terrainRB = m_Terrain.GetComponent<Rigidbody>();
    auto& terrainMesh = m_Terrain.GetComponent<MeshRenderer>();
    //terrainMesh.LoadFromHeightMap(assetPath + "terrain.png");
    terrainMesh.LoadFromOBJ(EnginePaths::AssetPath() + "terrain.obj");
    terrainRB.SetRigidbodyType(rp3d::BodyType::STATIC);
    terrainRB.SetPosition(rp3d::Vector3(0.0f, -10.0f, 0.0f));
    // terrainRB.SetRotation(rp3d::Vector3(0.0f, 90.0f, 0.0f));
    // terrainRB.AddConcaveColldier(terrainMesh.GetRawVertices(), terrainMesh.GetRawNormals(), terrainMesh.GetIndices());


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

void DefaultScene::Render(const std::unique_ptr<Renderer>& renderer, const std::shared_ptr<Shader> shader, Camera& camera, ObjectManager& objectManager)
{
    for (auto& ref : objectManager.objectRegistry)
    {
        auto& retrivedObject = *ref.second;
        auto& rigidbody = retrivedObject.GetComponent<Rigidbody>();
        auto& meshRenderer = retrivedObject.GetComponent<MeshRenderer>();
        renderer->Submit(rigidbody.GetOpenGLTransform(), meshRenderer.GetVertexArray(), meshRenderer.GetIndexBuffer(), shader, camera);
    }
}
