#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Setup()
{
	glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.1f, 0.1, 0.1f, 0.1f);
}

void Renderer::Submit(const glm::mat4& transform, std::shared_ptr<VertexArray> vertexArray, std::shared_ptr<IndexBuffer> indexBuffer, std::shared_ptr<Shader> shader, Camera& camera)
{

    shader->Bind();
    shader->UploadUniformMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
    shader->UploadUniformMat4("u_ViewMatrix", camera.GetViewMatrix());
    shader->UploadUniformVec3("u_ViewPos", camera.GetPosition());
    shader->UploadUniformMat4("u_Transform", transform);

    vertexArray->Bind();
    glDrawElements(GL_TRIANGLES, indexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

}
