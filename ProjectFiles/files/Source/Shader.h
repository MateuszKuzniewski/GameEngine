#pragma once
#include <string>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
class Shader
{
public:

	Shader(std::string& vertexShaderSrc, std::string& fragmentShaderSrc);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void UploadUniformFloat4(const std::string& name, const glm::vec4& value);
	void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
	void UploadUniformVec3(const std::string& name, const glm::vec3& vector);


private:
	
	uint32_t m_RendererID;

};

