#pragma once
#include <string>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "Window.h"
#include "GameObject.h"

class GUI
{

public:

	GUI(Window* window);
	~GUI();
	void PrepareRender();
	void Render();

private:

	void Shutdown();
	void StatisticsPanel();
	void SceneHierarchyPanel();
	void InspectorPanel();
	void MenuPanel();
	void DrawEntity(GameObject& gameObject);
	void DrawComponent(GameObject& object);


private:
	Window* m_Window;
	float m_WindowHeight, m_WindowWidth;

	
};

