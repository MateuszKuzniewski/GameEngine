#include "Camera.h"
#include <iostream>

Camera Camera::m_Instance;

Camera::Camera()
	: m_FOV(60), m_NearClip(0.1f), m_FarClip(1000.0f)
{
	
	UpdateViewMatrix();
	UpdateProjectionMatrix();

}

Camera::~Camera()
{

}


bool Camera::IsLeftMouseButtonPressed()
{
	if (m_LeftMouseButtonPressed)
		return true;
	return false;
}

bool Camera::IsRightMouseButtonPressed()
{
	if (m_RightMouseButtonPressed)
		return true;
	return false;
}


void Camera::UpdateProjectionMatrix()
{
	m_AspectRatio = m_WindowWidth / m_WindowHeight;
	m_ProjectionMatrix = glm::perspective(glm::radians(m_FOV), m_AspectRatio, m_NearClip, m_FarClip);

}

void Camera::UpdateViewMatrix()
{
	glm::quat orientation = GetOrientation();

	m_ViewMatrix = glm::translate(glm::mat4(1.0f), m_Position) * glm::mat4(orientation);
	m_ViewMatrix = glm::inverse(m_ViewMatrix);
}

glm::mat4 Camera::GetViewProjectionMatrix() 
{
	m_ViewProjectionMatrix =  m_ProjectionMatrix * m_ViewMatrix;
	return m_ViewProjectionMatrix;
}



void Camera::RegisterKeyboardInput(GLFWwindow* window)
{

	const float deltaSpeed = m_CameraSpeed * Time::GetDeltaTime();

	// z
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_Position -= deltaSpeed * glm::vec3(0.0f, 0.0f, 1.0f);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_Position += deltaSpeed * glm::vec3(0.0f, 0.0f, 1.0f);

	// x
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_Position -= deltaSpeed * glm::vec3(1.0f, 0.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_Position += deltaSpeed * glm::vec3(1.0f, 0.0f, 0.0f);

	// y
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		m_Position += deltaSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		m_Position -= deltaSpeed * glm::vec3(0.0f, 1.0f, 0.0f);


	

	UpdateViewMatrix();
}


void Camera::MouseRotate(const glm::vec2& delta)
{
	const float rotationSpeed = 0.005f;

	m_Yaw += delta.x * rotationSpeed;
	m_Pitch += delta.y * -rotationSpeed;
}

void Camera::MousePressedState(const bool& state, int button)
{
	switch (button)
	{
	case 0:
		m_LeftMouseButtonPressed = state;
		break;
	case 1:
		m_RightMouseButtonPressed = state;
		break;
	}
}


void Camera::MouseOrbit(const glm::vec2& delta)
{
	float deltaAngleX = (3.14f  / m_WindowWidth); // a movement from left to right = 2*PI = 360 deg
	float deltaAngleY = (3.14f / m_WindowHeight);  // a movement from top to bottom = PI = 180 deg

	float xAngle = delta.x * deltaAngleX * -1;
	float yAngle = delta.y * deltaAngleY * -1;
	
	// TO DO: FIX. camera direction facing up vector 
	// TO DO: FIX. rapid mouse motion messes up camera orientation


	glm::vec4 newPos(m_Position, 1.0f);
	glm::vec4 pivot(m_FocalPoint, 1.0f);

	glm::mat4 rotationMatrixX(1.0f);
	rotationMatrixX = glm::rotate(rotationMatrixX, xAngle, GetUpVector());
	glm::vec4 finalXPosition = (rotationMatrixX * (newPos - pivot)) + pivot;

	glm::mat4 rotationMatrixY(1.0f);
	rotationMatrixY = glm::rotate(rotationMatrixY, yAngle, GetRightDirection());
	glm::vec3 finalYPosition = (rotationMatrixY * (finalXPosition - pivot)) + pivot;

	m_Yaw -= xAngle;
	m_Pitch -= yAngle;
	m_Position = finalYPosition;


	
}

void Camera::MouseMove(const glm::vec2& delta)
{
	m_Position.y += delta.y;

}


glm::quat Camera::GetOrientation() const
{
	return glm::vec3(-m_Pitch, -m_Yaw, -m_Roll);
}

glm::mat4 Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}

static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	Camera& instance = Camera::GetInstance();

	if (button == GLFW_MOUSE_BUTTON_LEFT)
	{
		if (GLFW_PRESS == action)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			instance.MousePressedState(true, 0);
			
		}
		else if (GLFW_RELEASE == action)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			instance.MousePressedState(false, 0);
		}
	}

	if (button == GLFW_MOUSE_BUTTON_RIGHT)
	{
		if (GLFW_PRESS == action)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			instance.MousePressedState(true, 1);

		}
		else if (GLFW_RELEASE == action)
		{
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			instance.MousePressedState(false, 1);
		}
	}
}

static void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	Camera& instance = Camera::GetInstance();

	const float scaleFactor = 0.006f;
	
	glm::vec2 mouse{ xpos, ypos };
	glm::vec2 delta = (mouse - instance.m_InitialMousePosition);

	instance.m_InitialMousePosition = mouse;

	// Orbit
	if (instance.IsLeftMouseButtonPressed())
	{
		instance.MouseOrbit(delta);
		instance.UpdateViewMatrix();
	}

	// Move
	if (instance.IsRightMouseButtonPressed())
	{
		instance.MouseMove(delta * scaleFactor);
		instance.UpdateViewMatrix();
	}
	
}

void Camera::RegisterMouseInput(GLFWwindow* window)
{
	glfwSetMouseButtonCallback(window, MouseButtonCallback);
	glfwSetCursorPosCallback(window, CursorPositionCallback);
}







