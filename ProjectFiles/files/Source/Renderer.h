#pragma once
#include "GL/glew.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Camera.h"

class Renderer
{
public:

	Renderer();
	~Renderer();

	void Setup();
	void Submit(const glm::mat4& transform, std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<Shader> shader, Camera& camera);

private:


};

