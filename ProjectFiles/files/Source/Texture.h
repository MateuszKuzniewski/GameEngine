#pragma once
#include <cstdint>
#include <GL/glew.h>
#include <iostream>


class Texture
{

public:

	Texture(const std::string& path);
	~Texture();

	void Bind() const;
	void Unbind() const;
	uint32_t GetRendererID() const { return (int)m_RendererID; };


private:
	
	std::string m_Path;
	uint32_t m_RendererID;
};

