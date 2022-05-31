#include "GUI.h"

GUI::GUI(Window* window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
 
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window->GetWindow(), true);
    ImGui_ImplOpenGL3_Init("#version 460");
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


    ImGui::SetNextWindowSize(ImVec2(200, 100));
    ImGui::SetNextWindowPos(ImVec2(1080, 620));

    ImGui::Begin("Statistics");
    ImGui::Text("Average Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::End();

}

void GUI::SceneHierarchyPanel()
{
    ImGui::SetNextWindowSize(ImVec2(200, 620));
    ImGui::SetNextWindowPos(ImVec2(1080, 0));
    ImGui::Begin("Hierarchy");
    ImGui::Text("GameObject");
    ImGui::Text("Terrain");
    ImGui::End();

}

void GUI::InspectorPanel()
{
    ImGui::SetNextWindowSize(ImVec2(200, 720));
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Inspector");
    ImGui::End();
}
