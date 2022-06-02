#pragma once

#include "Renderer.h"
#include "Window.h"
#include "Texture.h"
#include "Component.h"
#include "Rigidbody.h"
#include "MeshRenderer.h"
#include "GUI.h"
#include "Input.h"
#include "ObjectManager.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

private:

	Window* m_AppWindow;
	Camera& m_CameraInstance = Camera::GetInstance();
	ObjectManager& m_ObjectManager = ObjectManager::GetInstance();

	std::unique_ptr<Texture> m_Texture;
	std::unique_ptr<Renderer> m_Renderer;
	std::unique_ptr<GUI> m_GUI;
	std::unique_ptr<Input> m_Input;
	std::shared_ptr<Shader> m_Shader;
	rp3d::PhysicsCommon m_PhysicsCommon;
	rp3d::PhysicsWorld* m_PhysicsWorld;
	rp3d::PhysicsWorld::WorldSettings m_WorldSettings;
	std::string WorkingDir;

};

