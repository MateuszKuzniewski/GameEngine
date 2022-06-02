#include <iostream>
#include "Window.h"


Window::Window(int size_x, int size_y, const char* title, GLFWmonitor* monitor, GLFWwindow* share) : m_Width(size_x), m_Height(size_y)
{
    if (!glfwInit())
        std::cout << "OpenGL: Failed to initilized GLFW" << std::endl;
    else
        std::cout << "OpenGL: Initialized GLFW" << std::endl;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(size_x, size_y, title, monitor, share);

    if (!window)
    {
        std::cout << "OpenGL: Failed to create window" << std::endl;
        glfwTerminate();
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK)
        std::cout << "OpenGL: Failed to initilized GLEW" << std::endl;
    else
        std::cout << "OpenGL: Initialized GLEW" << std::endl;

    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
  
}
Window::~Window()
{
    glfwTerminate();
}

void Window::Destroy()
{
    /* Destroy window without terminating GLFW */
    glfwDestroyWindow(window);
}

GLFWwindow* Window::GetWindow() const
{
    return window;
}


