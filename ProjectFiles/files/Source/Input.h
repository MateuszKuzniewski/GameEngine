#pragma once
#include "Window.h"
#include "Camera.h"
#include "imgui.h"
enum MouseCodes
{
	LeftMouseButton = 0,
	RightMouseButton = 1,
	MiddleMouseButton = 2
};

class Input
{
public:
	Input(Window* window);
	~Input();

	void RegisterMouseEvents();
	void RegisterKeyboardEvents();

private:

	Camera& m_Camera = Camera::GetInstance();
	ImGuiIO& m_IO = ImGui::GetIO();
	Window* m_Window;
	

};

