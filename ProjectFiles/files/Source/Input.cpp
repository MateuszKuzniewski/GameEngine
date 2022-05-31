#include "Input.h"

Input::Input(Window* window) : m_Window(window)
{

}

Input::~Input()
{
}

void Input::RegisterMouseEvents()
{
	const float scaleFactor = 0.006f;
	ImVec2 delta = m_IO.MouseDelta;
	glm::vec2 glmMouseDelta = glm::vec2(delta.x, delta.y);

	if (!m_IO.WantCaptureMouse)
	{
		if (m_IO.MouseDown[MouseCodes::LeftMouseButton]) 
		{
			glfwSetInputMode(m_Window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			m_Camera.MouseOrbit(glmMouseDelta);
			m_Camera.UpdateViewMatrix();
		}
		else if (m_IO.MouseDown[MouseCodes::RightMouseButton])
		{
			glfwSetInputMode(m_Window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			m_Camera.MouseMove(glmMouseDelta * scaleFactor);
			m_Camera.UpdateViewMatrix();
		}
		else
		{
			glfwSetInputMode(m_Window->GetWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}

void Input::RegisterKeyboardEvents()
{

	if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_A) == GLFW_PRESS)
		m_Camera.Move(MoveDirection::LEFT);
	if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_D) == GLFW_PRESS)
		m_Camera.Move(MoveDirection::RIGHT);

	// y
	if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_SPACE) == GLFW_PRESS)
		m_Camera.Move(MoveDirection::UP);
	if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_C) == GLFW_PRESS)
		m_Camera.Move(MoveDirection::DOWN);


	// z
	if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_W) == GLFW_PRESS)
		m_Camera.Move(MoveDirection::FORWARD);
	if (glfwGetKey(m_Window->GetWindow(), GLFW_KEY_S) == GLFW_PRESS)
		m_Camera.Move(MoveDirection::BACKWARD);

}
