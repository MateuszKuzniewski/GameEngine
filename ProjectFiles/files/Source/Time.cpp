#include "Time.h"
#include "GLFW/glfw3.h"


Time::Time()
{
}

Time::~Time()
{
}

float Time::GetDeltaTime()
{

	float currentFrame = glfwGetTime();
	float lastFrame = 0.0f;
	float deltaTime = currentFrame - lastFrame;
	return deltaTime;
}
