#pragma once
#include <string>
#include <memory>
#include <SDL_pixels.h>
#include <glm/vec3.hpp>

#include "RenderComponent.h"

namespace Monke
{
	class Font;
	class Texture2D;
	class Transform;

	class Text final : public RenderComponent
	{
	public:

		explicit Text(const std::weak_ptr<GameObject>& pParent);
		virtual ~Text() override = default;


		void Render() const override;

		void SetText(const std::string& text) { m_Text = text; ChangeTextTexture(); }
		void SetFont(const std::shared_ptr<Font>& font) { m_pFont = font; ChangeTextTexture(); }

		void SetColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a = 255) { m_Color = { r, g, b, a }; ChangeTextTexture(); }
		void SetColor(const int r, const int g, const int b, const int a = 255) { m_Color = { static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a)}; ChangeTextTexture(); }
		void SetColor(const SDL_Color& color) { m_Color = color; ChangeTextTexture(); }


		Text(const Text& other) = delete;
		Text(Text&& other) = delete;
		Text& operator=(const Text& other) = delete;
		Text& operator=(Text&& other) = delete;

	private:

		void ChangeTextTexture();

		//weak pointer of the transform to draw the text on the right position
		std::weak_ptr<Transform> m_pTransform{};

		std::string m_Text{" "};

		//texture pointers
		std::shared_ptr<Font> m_pFont{};
		std::shared_ptr<Texture2D> m_pTextTexture{};

		//default white
		SDL_Color m_Color{ 255, 255, 255, 255 };

	};
}
