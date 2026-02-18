#pragma once
#include "Component.h"
#include "RenderComponent.h"
#include"SDL3/SDL.h"

namespace dae
{
	class GameObject;

	class TextComponent final :public Component
	{
	public:
		TextComponent(std::shared_ptr<RenderComponent> pRenderComponent = nullptr, std::shared_ptr<Font> pFont = nullptr, int priority = -1);
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void SetTextToTexture(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
		void SetColor(const SDL_Color & color);

	private:
		std::shared_ptr<RenderComponent> m_pRenderComponent;
		std::shared_ptr<Font> m_pFont;
		SDL_Color m_Color{ 255,255,255 };
	};
}
