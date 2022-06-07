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
    ImGui::Text("Version: 0.1.7");
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
    ImGui::SetNextWindowSize(ImVec2(300, m_WindowHeight - offset));
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


                if(ImGui::BeginCombo("Body type", bodyTypePreview.c_str()))
                {
                    bool isSelected = false;
                    if (ImGui::Selectable("static", isSelected ))
                    {
                        bodyTypePreview = "static";
                    }
                    if (ImGui::Selectable("dynamic", isSelected))
                    {

                        bodyTypePreview = "dynamic";
                    }
                    if(ImGui::Selectable("kinematic", isSelected))
                    {

                        bodyTypePreview = "kinematic";
                    }


                    ImGui::EndCombo();
                }
                    

                ImGui::Checkbox("Gravity", &component.isGravity);
                component.EnableGravity(component.isGravity);
                ImGui::TreePop();
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
    ImGui::EndMainMenuBar();
}

