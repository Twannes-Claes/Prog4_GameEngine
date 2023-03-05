#pragma once

#include <sstream>

#include "UpdateComponent.h"

namespace Monke
{
	class Time;
	class Text;

	class FPS final : public UpdateComponent
	{
	public:

		explicit FPS(std::weak_ptr<GameObject> parent);
		virtual ~FPS() override = default;

		virtual void Initialize() override;
		virtual void Update() override;

		int GetFPS() const { return m_FPS; }

		FPS(const FPS& other) = delete;
		FPS(FPS&& other) = delete;
		FPS& operator=(const FPS& other) = delete;
		FPS& operator=(FPS&& other) = delete;

	private:

		std::weak_ptr<Text> m_pText{};

		const float m_TimeToUpdate{ 0.15f };

		float m_ResetTimer{};

		int m_FPS{};

		int m_NewFPS{};

		std::stringstream m_StreamFPS{};

	};
}
