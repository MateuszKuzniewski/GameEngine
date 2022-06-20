#include "GUI.h"
#include "ObjectManager.h"
#include "Rigidbody.h"
#include "MeshRenderer.h"

GUI::GUI(Window* window) : m_Window(window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
 
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");

    m_WindowWidth = m_Window->GetWindowWidth();
    m_WindowHeight = m_Window->GetWindowHeight();

}

GUI::~GUI()
{
    Shutdown();
}

void GUI::Shutdown()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void GUI::PrepareRender()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

void GUI::Render()
{

    StatisticsPanel();
    SceneHierarchyPanel();
    InspectorPanel();
    MenuPanel();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

}

void GUI::StatisticsPanel()
{
    //ImGui::Begin("Scene");
    //ImGui::Text("Scene Colour");
    //ImGui::ColorEdit4("Colour", sceneColour);
    //ImGui::End();
  
    ImGui::SetNextWindowSize(ImVec2(300, 100));
    ImGui::SetNextWindowPos(ImVec2(m_WindowWidth - 300, m_WindowHeight - 100));
    ImGui::Begin("Statistics");
    ImGui::Text("Version: 0.1.8");
    ImGui::Text("--------------");
    ImGui::Text("Average Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();

}

void GUI::SceneHierarchyPanel()
{
    ObjectManager& objectManager = ObjectManager::GetInstance();

    ImGui::SetNextWindowSize(ImVec2(300, m_WindowHeight - 120));
    ImGui::SetNextWindowPos(ImVec2(m_WindowWidth - 300, m_WindowHeight - (m_WindowHeight - 20)));

    ImGui::Begin("Hierarchy");
    ImGui::Separator();
    for (const auto& object : objectManager.objectRegistry)
    {
        auto& retrivedObject = *object.second;
        DrawEntity(retrivedObject);
    }
    
    ImGui::End();

}

void GUI::InspectorPanel()
{
    ObjectManager& objectManager = ObjectManager::GetInstance();
   
    float offset = 20.0f;
    ImGui::SetNextWindowSize(ImVec2(350, m_WindowHeight - offset));
    ImGui::SetNextWindowPos(ImVec2(0, m_WindowHeight - (m_WindowHeight - offset)));
    ImGui::Begin("Inspector");
    ImGui::Separator();
    for (const auto& object : objectManager.objectRegistry)
    {
        auto& retrivedObject = *object.second;
        DrawComponent(retrivedObject);

        if (ImGui::IsMouseClicked(0) && !ImGui::GetIO().WantCaptureMouse)
        {
            retrivedObject.isSelected = false;
        }
    }


    ImGui::End();
}

void GUI::DrawEntity(GameObject& gameObject)
{
    ObjectManager& objectManager = ObjectManager::GetInstance();
    ImGuiTreeNodeFlags flags =  ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_SpanAvailWidth ;
    if (gameObject.isSelected) flags |= ImGuiTreeNodeFlags_Selected;

    bool opened = ImGui::TreeNodeEx(gameObject.name.c_str(), flags);

    if (ImGui::IsItemHovered())
    {
        ImGui::BeginTooltip();
        ImGui::TextUnformatted("Tooltip text");
        ImGui::EndTooltip();
    }

    if (ImGui::IsItemClicked())
    {
        int objectID = gameObject.GetID();
        for (const auto& object : objectManager.objectRegistry)
        {
            auto& retrivedObject = *object.second;
            if (retrivedObject.GetID() != objectID)
            {
                retrivedObject.isSelected = false;
            }
        }
        //bool isClicked = (gameObject.isSelected) ? false : true;
        gameObject.isSelected = true;

      
    }

    if (opened)
    {
        ImGui::TreePop();
    }

}

void GUI::DrawComponent(GameObject& object)
{
    const ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Framed | ImGuiTreeNodeFlags_SpanAvailWidth | ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding;
    std::string componentName = "";    
   
    if (object.isSelected)
    {
        if (object.HasComponent<Rigidbody>())
        {
            componentName = "Rigidbody";
            auto& component = object.GetComponent<Rigidbody>();
            bool opened = ImGui::TreeNodeEx(componentName.c_str(), flags);
        

            if (opened)
            {
                float posSlider[3] = { component.GetPosition().x, component.GetPosition().y, component.GetPosition().z };
                ImGui::DragFloat3("position", posSlider, 0.5f, 0.0f);
                component.SetPosition(rp3d::Vector3(posSlider[0], posSlider[1], posSlider[2]));

                float rotSlider[3] = { component.GetEulerRotation().x, component.GetEulerRotation().y, component.GetEulerRotation().z };
                ImGui::DragFloat3("rotation", rotSlider, 0.5f, 0.0f);
                component.SetRotation(rp3d::Vector3(rotSlider[0], rotSlider[1], rotSlider[2]));

                
                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Separator();


                //----------------------- Rigidbody -----------------------------------------

                if (ImGui::BeginCombo("body type", component.GetBodyTypeString().c_str()))
                {
                    bool isSelected = false;
                    if (ImGui::Selectable("static", isSelected ))
                    {
                        component.SetRigidbodyType(rp3d::BodyType::STATIC);
                    }
                    if (ImGui::Selectable("dynamic", isSelected))
                    {
                        component.SetRigidbodyType(rp3d::BodyType::DYNAMIC);
                     
                    }
                    if(ImGui::Selectable("kinematic", isSelected))
                    {
                        component.SetRigidbodyType(rp3d::BodyType::KINEMATIC);
                    }

                    ImGui::EndCombo();
                }

                if (component.GetBodyTypeString() == "dynamic")
                {
                    ImGui::Checkbox("gravity", &component.isGravity);
                    component.EnableGravity(component.isGravity);
                }

                ImGui::Spacing();
                ImGui::Spacing();
                ImGui::Separator();


                //----------------------- Collider -----------------------------------------
                if (ImGui::Button("x", ImVec2(20, 20)))
                {
                    component.RemoveCollider();
                }

                ImGui::SameLine();

                if (ImGui::BeginCombo("collider", component.GetColliderTypeString().c_str()))
                {

                    bool isSelected = false;
                  
                    if (ImGui::Selectable("box", isSelected))
                    {
                        component.AddBoxCollider(component.colliderSizeVec3);
                    }
                    if (ImGui::Selectable("sphere", isSelected))
                    {
                        component.AddSphereCollider(component.sphereRadius);
                    }
                    if (ImGui::Selectable("mesh", isSelected))
                    {
                        if(object.HasComponent<MeshRenderer>())
                        {
                            auto& mesh = object.GetComponent<MeshRenderer>();
                            component.AddConcaveColldier(mesh.GetRawVertices(), mesh.GetRawNormals(), mesh.GetIndices());
                        }
                        else
                        {
                            std::cout << "Trying to add mesh collider to an object without MeshRenderer component \n";
                            exit(1);
                        }
                    }

                    ImGui::EndCombo();
                }
              
                
                
                if (component.GetColliderTypeString() == "box")
                {
                    float sizeSlider[3] = { component.colliderSizeVec3.x, component.colliderSizeVec3.y, component.colliderSizeVec3.z };
                    ImGui::DragFloat3("size", sizeSlider, 0.5f, 0.0f);
                    component.colliderSizeVec3 = rp3d::Vector3(sizeSlider[0], sizeSlider[1], sizeSlider[2]);
                }
                else if (component.GetColliderTypeString() == "sphere")
                {
                    ImGui::DragFloat("radius", &component.sphereRadius, 0.5f, 0.0f);
                }
                else if (component.GetColliderTypeString() == "mesh") {}

                ImGui::TreePop();
                ImGui::Spacing();
                ImGui::Spacing();  
                ImGui::Spacing();  
                ImGui::Spacing();

            }
        }

        if (object.HasComponent<MeshRenderer>())
        {
            componentName = "MeshRenderer";
            auto& component = object.GetComponent<MeshRenderer>();
            bool opened = ImGui::TreeNodeEx(componentName.c_str(), flags);
            if (opened) ImGui::TreePop();
        }
    }

}

void GUI::MenuPanel()
{
    ImGui::BeginMainMenuBar();
    ImGui::MenuItem("FILE");
    ImGui::MenuItem("EDIT");
    ImGui::MenuItem("ASSETS");
    ImGui::MenuItem("WINDOW");
    ImGui::MenuItem("HELP");

    {
        ImVec2 buttonSize = { 40, 20 };
        float buttonOffset = 42;
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
        ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.8f, 0.8f));

        // minimize button
        ImGui::SetCursorPosX(m_WindowWidth - buttonOffset * 3);
        if (ImGui::Button("-", buttonSize))
        {
            m_Window->MinimizeWindow();
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::TextUnformatted("Minimize Window");
            ImGui::EndTooltip();
        }

        // maximize button
        ImGui::SetCursorPosX(m_WindowWidth - buttonOffset * 2);
        if (ImGui::Button("[]", buttonSize))
        {
            //m_Window->MinimizeWindow();
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::TextUnformatted("Maximize Window");
            ImGui::EndTooltip();
        }

        // close button
        ImGui::SetCursorPosX(m_WindowWidth - buttonOffset);
        if (ImGui::Button("X", buttonSize))
        {
           
            m_Window->CloseWindow();
        }
        if (ImGui::IsItemHovered())
        {
            ImGui::BeginTooltip();
            ImGui::TextUnformatted("Close Window");
            ImGui::EndTooltip();
        }
    }
    ImGui::PopStyleColor(2);
    ImGui::EndMainMenuBar();
}

