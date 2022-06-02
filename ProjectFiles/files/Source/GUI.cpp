#include "GUI.h"
#include "ObjectManager.h"

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
    ImGui::Text("Version: 0.1.6");
    ImGui::Text("--------------");
    ImGui::Text("Average Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();

}

void GUI::SceneHierarchyPanel()
{
    ObjectManager& objectManager = ObjectManager::GetInstance();

    ImGui::SetNextWindowSize(ImVec2(300, m_WindowHeight - 100));
    ImGui::SetNextWindowPos(ImVec2(m_WindowWidth - 300, 0));

    ImGui::Begin("Hierarchy");
    
    for (const auto& object : objectManager.objectRegistry)
    {
        auto& retrivedObject = *object.second;
        DrawEntity(retrivedObject);
    }

    ImGui::End();

}

void GUI::DrawEntity(GameObject& gameObject)
{
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
        std::cout << gameObject.GetID() << std::endl;
        bool isClicked = (gameObject.isSelected) ? false : true;
        gameObject.isSelected = isClicked;
    }

    if (opened)
    {
        ImGui::TreePop();
    }

}

void GUI::InspectorPanel()
{
    ImGui::SetNextWindowSize(ImVec2(300, m_WindowHeight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Inspector");
    ImGui::End();
}

