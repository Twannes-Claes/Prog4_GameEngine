#pragma once
#include <string>
#include <memory>
#include <SDL_pixels.h>

#include "RenderComponent.h"

namespace Monke
{
	class Font;
	class Texture2D;

	class Text final : public RenderComponent
	{
	public:

		explicit Text(std::weak_ptr<GameObject>& pParent, std::string text, std::shared_ptr<Font> font);

		void Render() const override;

		void SetText(const std::string& text) { m_Text = text; ChangeTextTexture(); }
		void SetFont(const std::shared_ptr<Font>& font) { m_pFont = font; ChangeTextTexture(); }

		void SetColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) { m_Color = { r, g, b, a }; ChangeTextTexture(); }
		void SetColor(const SDL_Color& color) { m_Color = color; ChangeTextTexture(); }


		virtual ~Text() override = default;

		Text(const Text& other) = delete;
		Text(Text&& other) = delete;
		Text& operator=(const Text& other) = delete;
		Text& operator=(Text&& other) = delete;

	private:

		void ChangeTextTexture();

		//std::weak_ptr<TextComponent> pComp;

		std::string m_Text;

		//texture pointers
		std::shared_ptr<Font> m_pFont;
		std::shared_ptr<Texture2D> m_pTextTexture;

		//default white
		SDL_Color m_Color{ 255, 255, 255, 255 };

	};
}
