#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/quaternion.hpp>
#include "Time.h"

enum MoveDirection
{
	UP, DOWN, LEFT, RIGHT, FORWARD, BACKWARD
};

class Camera
{
public:
	Camera(const Camera&) = delete;
	
	static Camera& GetInstance()
	{
		return s_Instance;
	}

	void Move(MoveDirection direction);
	void UpdateProjectionMatrix();
	void UpdateViewMatrix();
	void MouseRotate(const glm::vec2& delta);
	void MouseOrbit(const glm::vec2& delta);
	void MouseMove(const glm::vec2& delta);

	glm::vec3 GetOrientation() const;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetViewProjectionMatrix();
	glm::vec3 GetUpVector() const { return m_UpVector; };
	glm::vec3 GetRightDirection() const { return glm::transpose(m_ViewMatrix)[0]; }
	glm::vec3 GetViewDir() const { return -glm::transpose(m_ViewMatrix)[2]; }
	glm::vec3 GetPosition() const { return m_Position;  }
	glm::vec3 GetForwardVector() { return m_ForwardVector; }


private:

	Camera();
	~Camera();

	glm::vec3 m_Position = { 0.0f, -2.0f, 15.0f };
	glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_UpVector = { 0.0f, 1.0f, 0.0f };
	glm::vec3 m_RightVector = { 1.0f, 0.0f, 0.0f };
	glm::vec3 m_ForwardVector = { 0.0f, 0.0f, -1.0f };


	float m_CameraSpeed = 0.01f;

	float m_FOV;
	float m_AspectRatio;
	float m_NearClip, m_FarClip;
	float m_Yaw, m_Pitch, m_Roll;

	float m_WindowWidth = 1280;
	float m_WindowHeight = 720;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewProjectionMatrix;
	
	static Camera s_Instance;

};

