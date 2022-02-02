#pragma once
#include "GL/glew.h"
#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"

class Renderer
{
public:

	Renderer();
	~Renderer();

	void Setup();
	void Submit(std::shared_ptr<GameObject> gameObject, std::shared_ptr<Shader> shader, Camera& camera);

private:


};

