#pragma once

#include "Renderer.h"
#include "Window.h"
#include "Texture.h"
#include "Component.h"
#include "BoxCollider.h"
#include "CapsuleCollider.h"
#include "SphereCollider.h"
#include <reactphysics3d/reactphysics3d.h>

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
	std::shared_ptr<GameObject> m_Ground;
	std::unique_ptr<Renderer> m_Renderer;
	rp3d::PhysicsCommon m_PhysicsCommon;
	rp3d::PhysicsWorld* m_PhysicsWorld;
	rp3d::PhysicsWorld::WorldSettings m_WorldSettings;
	std::string WorkingDir;

};

