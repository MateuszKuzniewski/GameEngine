#pragma once

#include "Renderer.h"
#include "Window.h"
#include "Texture.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

private:

	Window* m_AppWindow;
	Camera& m_CameraInstance = Camera::GetInstance();
	std::shared_ptr<Shader> m_Shader;
	std::unique_ptr<Texture> m_Texture;
	std::shared_ptr<GameObject> m_MonkeyHead;
	std::shared_ptr<GameObject> m_MonkeyHead2;
	std::shared_ptr<GameObject> m_Ground;
	std::unique_ptr<Renderer> m_Renderer;
	std::string WorkingDir;


};

