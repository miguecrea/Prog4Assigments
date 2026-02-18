#pragma once
#include "Component.h"
#include <string>
#include <memory>
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;
	class Texture2D;
	class Font;

	class RenderComponent final: public Component
	{
	public:
		virtual void Render() override;

		void SetTexture(const std::string& filename);
		void SetTexture(std::shared_ptr<Texture2D> pTexture);

		RenderComponent(int priority = -2);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

	private:
		std::shared_ptr<Texture2D> m_pTexture{};
		glm::vec3 m_LastPosition{};
	};
}

