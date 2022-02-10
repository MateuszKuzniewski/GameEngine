#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include <gtc/quaternion.hpp>

class Camera
{
public:
	Camera(const Camera&) = delete;
	
	static Camera& GetInstance()
	{
		return m_Instance;
	}

	void RegisterKeyboardInput(GLFWwindow* window);
	void RegisterMouseInput(GLFWwindow* window);
	void UpdateProjectionMatrix();
	void UpdateViewMatrix();
	void MouseRotate(const glm::vec2& delta);
	void MousePressedState(const bool& state, int button);
	void MouseOrbit(const glm::vec2& delta);
	void MouseMove(const glm::vec2& delta);




	glm::quat GetOrientation() const;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetViewProjectionMatrix();
	glm::vec3 GetUpVector() const { return m_UpVector; };
	glm::vec3 GetRightDirection() const { return glm::transpose(m_ViewMatrix)[0]; }
	glm::vec3 GetViewDir() const { return -glm::transpose(m_ViewMatrix)[2]; }
	glm::vec3 GetPosition() const { return m_Position;  }
	glm::vec3 GetForwardVector() { return m_ForwardVector; }



	glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };
	glm::vec2 m_MousePos = { 0.0f, 0.0f };

	bool IsLeftMouseButtonPressed();
	bool IsRightMouseButtonPressed();

private:

	Camera();
	~Camera();

	glm::vec3 m_Position = { 0.0f, 0.0f, 2.0f };
	glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };
	glm::vec3 m_UpVector = { 0.0f, 1.0f, 0.0f };
	glm::vec3 m_RightVector = { 1.0f, 0.0f, 0.0f };
	glm::vec3 m_ForwardVector = { 0.0f, 0.0f, -1.0f };


	float m_CameraSpeed = 0.0003f;

	float m_FOV;
	float m_AspectRatio;
	float m_NearClip, m_FarClip;
	float m_Yaw, m_Pitch, m_Roll;

	float m_WindowWidth = 1280;
	float m_WindowHeight = 720;

	bool m_LeftMouseButtonPressed;
	bool m_RightMouseButtonPressed;

	glm::mat4 m_ViewMatrix;
	glm::mat4 m_ProjectionMatrix;
	glm::mat4 m_ViewProjectionMatrix;
	


	static Camera m_Instance;

};

