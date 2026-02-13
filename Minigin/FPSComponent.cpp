#include "FPSComponent.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include <string>
#include <iostream>
#include"GameObject.h"

void dae::FPSComponent::Update()
{

    const float deltaTime{ SceneManager::GetInstance().GetDeltaTime() };

    ++m_NrFrames;
    m_ElapsedTime += deltaTime;

    if (m_ElapsedTime >= m_RefreshTime)
    {
        const int currentFrameRate{
            static_cast<int>(std::round(m_NrFrames / m_ElapsedTime))
        };

        if (currentFrameRate != m_FrameRate)
        {
            m_FrameRate = currentFrameRate;

            if (m_pTextComponent)
            {
                m_pTextComponent->SetTextToTexture(
                    std::to_string(m_FrameRate) + " FPS"
                );
            }
        }

        m_NrFrames = 0;
        m_ElapsedTime -= m_RefreshTime; // prevents drift
    }
}

dae::FPSComponent::FPSComponent(std::shared_ptr<TextComponent> pTextComponent, float waitingTime, int priority)
	:Component(priority), m_pTextComponent{ pTextComponent }, m_RefreshTime{ std::max(0.f, waitingTime) }
{


}
