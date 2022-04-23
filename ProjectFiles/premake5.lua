workspace "OpenGL_Premake"
	architecture "x64"
	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "OpenGL_Premake"

	location "files"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	
	defines { "GLEW_STATIC" }

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	includedirs { "Dependencies/GLFW/include", "Dependencies/GLEW/include/", "Dependencies/GLM", "Dependencies/ReactPhysics3D/include"}
	libdirs { "Dependencies/GLFW/lib-vc2022", "Dependencies/GLEW/lib/Release/x64", "Dependencies/ReactPhysics3D/lib"}
	
	files { "files/**.h", "files/**.cpp"}
	

	links { "glfw3", "glew32s", "opengl32", "reactphysics3d" }
	
	filter "system:windows"
		systemversion "latest"
	

	filter "configurations:Debug"
		defines { "DEBUG" }
		symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }
	
