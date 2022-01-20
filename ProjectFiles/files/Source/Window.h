#pragma once
#include <GL/glew.h> 
#include <GLFW/glfw3.h>


class Window
{
public:

	Window(int size_x, int size_y, const char* title, GLFWmonitor* monitor, GLFWwindow* share);
	~Window();

	void Destroy();
	GLFWwindow* GetWindow() const;
	
private:

	GLFWwindow* window;

};

