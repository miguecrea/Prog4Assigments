#include "SineMovementComponent.h"
#include "SceneManager.h"
#include "GameObject.h"

void dae::SineMovementComponent::FixedUpdate()
{
	const float deltaTime{ SceneManager::GetInstance().GetFixedTimeStep() };//get delta time 
	
	m_Angle += m_CycleSpeed * deltaTime;  //cycle is 
	
	const float posX{ m_Origin.x + m_Radius * cos(m_Angle) };  // the
	const float posY{ m_Origin.y + m_Radius * sin(m_Angle) };

	GetOwner()->SetPosition(posX, posY);
}

dae::SineMovementComponent::SineMovementComponent(const glm::vec3& origin, float radius, float nrSeconds, int priority)
	:Component(priority), m_Origin{ origin }, m_Radius{ radius }, m_CycleSpeed{ (2.f * 3.14159f) / nrSeconds }
{
}

void dae::SineMovementComponent::SetLocalOrigin(const glm::vec3& origin)
{
	m_Origin = origin;
}

void dae::SineMovementComponent::SetRadius(float radius)
{
	m_Radius = radius;
}

void dae::SineMovementComponent::SetCycleTime(float nrSeconds)
{
	m_CycleSpeed = (2.f * 3.14159f) / nrSeconds; //2 Pi   o 360         /


}
