#include "Camera.h"

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



void Camera::Move(MoveDirection direction)
{

	const float deltaSpeed = m_CameraSpeed;

	// x
	if (direction == MoveDirection::LEFT)
		m_Position -= deltaSpeed * GetRightDirection();
	if (direction == MoveDirection::RIGHT)
		m_Position += deltaSpeed * GetRightDirection();

	// y
	if (direction == MoveDirection::UP)
		m_Position += deltaSpeed * glm::vec3(0.0f, 1.0f, 0.0f);
	if (direction == MoveDirection::DOWN)
		m_Position -= deltaSpeed * glm::vec3(0.0f, 1.0f, 0.0f);


	// z
	if (direction == MoveDirection::FORWARD)
		m_Position += deltaSpeed * GetViewDir();
	if (direction == MoveDirection::BACKWARD)
		m_Position -= deltaSpeed * GetViewDir();

	
	UpdateViewMatrix();
}


void Camera::MouseRotate(const glm::vec2& delta)
{
	const float rotationSpeed = 0.005f;

	m_Yaw += delta.x * rotationSpeed;
	m_Pitch += delta.y * -rotationSpeed;
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


glm::vec3 Camera::GetOrientation() const
{
	return glm::vec3(-m_Pitch, -m_Yaw, -m_Roll);
}

glm::mat4 Camera::GetViewMatrix() const
{
	return m_ViewMatrix;
}









