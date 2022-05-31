#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "Window.h"

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


};

