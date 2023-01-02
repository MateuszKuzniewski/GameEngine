#pragma once

#include "Renderer.h"
#include "Window.h"
#include "Texture.h"
#include "Component.h"
#include "GUI.h"
#include "DefaultScene.h"
#include "ParticleSystemScene.h"
#include "Input.h"
#include "ObjectManager.h"
#include "EnginePaths.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	void Initialize();

private:

	Component componentData;
	Window* m_AppWindow;
	Camera& m_CameraInstance = Camera::GetInstance();
	ObjectManager& m_ObjectManager = ObjectManager::GetInstance();

	std::unique_ptr<Scene> m_Scene;
	std::unique_ptr<DefaultScene> m_DefaultScene;
//	std::unique_ptr<ParticleSystemScene> m_ParticleScene;

	std::unique_ptr<GUI> m_GUI;
	std::unique_ptr<Input> m_Input;
	std::shared_ptr<Shader> m_Shader;
	std::shared_ptr<Shader> m_particleShader;
	std::unique_ptr<Texture> m_Texture;
	std::unique_ptr<Renderer> m_Renderer;

	rp3d::PhysicsCommon m_PhysicsCommon;
	rp3d::PhysicsWorld* m_PhysicsWorld;
	rp3d::PhysicsWorld::WorldSettings m_WorldSettings;

};

