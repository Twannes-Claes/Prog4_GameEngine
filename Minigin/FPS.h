#pragma once

#include <sstream>

#include <memory>
#include <SDL_pixels.h>

#include "BaseComponent.h"

namespace Monke
{
	class Time;
	class Font;
	class Text;

	class FPS final : public BaseComponent
	{
	public:

		explicit FPS( GameObject* parent, const std::shared_ptr<Font>& pFont, const SDL_Color& color);
		virtual ~FPS() override = default;

		virtual void Update() override;

		int GetFPS() const { return m_FPS; }

		FPS(const FPS& other) = delete;
		FPS(FPS&& other) = delete;
		FPS& operator=(const FPS& other) = delete;
		FPS& operator=(FPS&& other) = delete;

	private:

		Text* m_pText{};

		const float m_TimeToUpdate{ 0.15f };

		float m_ResetTimer{};

		int m_FPS{};

		int m_NewFPS{};

		std::stringstream m_StreamFPS{};

	};
}
