#include "GUI.h"
#include "ObjectManager.h"
#include "Rigidbody.h"
#include "MeshRenderer.h"
#include <filesystem>

GUI::GUI(Window* window) : m_Window(window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
 
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");

    m_WindowWidth = m_Window->GetWindowWidth();
    m_WindowHeight = m_Window->GetWindowHeight();

    std::string projectPath = std::filesystem::current_path().parent_path().string();
    std::string assetPath = projectPath + "\\Resources\\";
    m_PlayIcon = std::make_unique<Texture>(assetPath + "playIcon.png");
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
    // PlayModeBar();
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

    ImGui::SetNextWindowSize(ImVec2(300, m_WindowHeight - 124));
    ImGui::SetNextWindowPos(ImVec2(m_WindowWidth - 300, m_WindowHeight - (m_WindowHeight - 24)));

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
   
    float offset = 24.0f;
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

    ImVec2 menuBarPadding = { 0,6 };
    ImVec2 buttonSize = { 40, 26 };
    float buttonOffset = 42;
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, menuBarPadding);
    ImGui::BeginMainMenuBar();
    ImGui::SetCursorPosX(20);
    ImGui::MenuItem("File");
    ImGui::MenuItem("Edit");
    ImGui::MenuItem("Assets");
    ImGui::MenuItem("Window");
    ImGui::MenuItem("Help");


    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(7.0f, 0.7f, 0.7f));
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(7.0f, 0.8f, 0.8f));

    // minimize button
    {
       
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
    }


    // maximize button
    {
       
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
    }


    // close button
    {
      
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
    ImGui::PopStyleVar(1);

   
    
}

void GUI::PlayModeBar()
{

    ImVec2 buttonSize = { 40,40 };
    ImGuiWindowFlags flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBackground;
    // ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0.0f);
    //ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 15.0f);
   // ImGui::SetNextWindowPos(ImVec2(m_WindowWidth / 2, 26));
    //ImGui::SetNextWindowBgAlpha(0.7);
    
    ImGui::Begin("Window ");
    if (ImGui::BeginChild("child"))
    {
        ImDrawList* drawList = ImGui::GetWindowDrawList();
        ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0, 0, 0, 0.8f));
       // ImGui::Image(0, buttonSize, ImVec2(0, 0), ImVec2(1, 1)); ImGui::SameLine();
        ImGui::ImageButton((ImTextureID)m_PlayIcon->GetRendererID(), buttonSize, ImVec2(0, 0), ImVec2(1, 1), 0);
        drawList->AddRect(ImGui::GetItemRectMin(), ImGui::GetItemRectMax(), IM_COL32(255, 255, 0, 255), 5.0f);
        ImGui::PopStyleColor(2);
        ImGui::EndChild();
    }


    ImGui::End();


}
