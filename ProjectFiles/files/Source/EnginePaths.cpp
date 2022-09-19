#include "EnginePaths.h"
#include <filesystem>


std::string EnginePaths::AssetPath()
{
	static std::string projectPath = std::filesystem::current_path().parent_path().string();
	static std::string assetPath = projectPath + "\\Resources\\";
	return assetPath;
}

std::string EnginePaths::ShaderPath()
{
	static std::string projectPath = std::filesystem::current_path().parent_path().string();
	static std::string shaderPath = projectPath + "\\files\\" + "\\Shaders\\";
	return shaderPath;
}
