#include "EnginePaths.h"
#include <filesystem>


std::string EnginePaths::ProjectPath()
{
	return std::filesystem::current_path().parent_path().string();
}


std::string EnginePaths::AssetPath()
{
	static std::string projectPath = ProjectPath();
	static std::string assetPath = projectPath + "\\Resources\\";
	return assetPath;
}

std::string EnginePaths::ShaderPath()
{
	static std::string projectPath = ProjectPath();
	static std::string shaderPath = projectPath + "\\files\\" + "\\Shaders\\";
	return shaderPath;
}

