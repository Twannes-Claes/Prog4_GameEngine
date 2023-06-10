#pragma once
#include <string>
#include <memory>
#include <SDL_pixels.h>
#include <glm/vec3.hpp>

#include "BaseComponent.h"

namespace Monke
{
	class Texture;
	class Font;
	class Texture2D;
	class Transform;

	class Text final : public BaseComponent
	{
	public:

		explicit Text( GameObject* parent, const std::shared_ptr<Font>& font, const std::string& text, const SDL_Color& color );
		explicit Text( GameObject* parent, const std::shared_ptr<Font>& font, const std::string& text);

		virtual ~Text() override = default;

		virtual void Update() override;

		void SetText(const std::string& text) { m_Text = text; m_NeedsUpdate = true; }
		void SetFont(const std::shared_ptr<Font>& font) { m_pFont = font; m_NeedsUpdate = true; }

		void SetColor(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a = 255) { m_Color = { r, g, b, a }; m_NeedsUpdate = true; }
		void SetColor(const int r, const int g, const int b, const int a = 255) { m_Color = { static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a)}; m_NeedsUpdate = true; }
		void SetColor(const SDL_Color& color) { m_Color = color; m_NeedsUpdate = true; }


		Text(const Text& other) = delete;
		Text(Text&& other) = delete;
		Text& operator=(const Text& other) = delete;
		Text& operator=(Text&& other) = delete;

	private:

		void ChangeTextTexture();

		bool m_NeedsUpdate{ true };

		//pointer of the transform to draw the text on the right position
		Transform* m_pTransformComp{};
		Texture* m_pTextureComp{};

		std::string m_Text{" "};

		//texture pointers
		std::shared_ptr<Font> m_pFont{};
		std::shared_ptr<Texture2D> m_pTextTexture{};

		//default white
		SDL_Color m_Color{ 255, 255, 255, 255 };

	};
}
