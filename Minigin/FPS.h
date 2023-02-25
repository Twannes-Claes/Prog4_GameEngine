#pragma once

#include "UpdateComponent.h"

namespace Monke
{

	class Text;

	class FPS final : public UpdateComponent
	{
	public:

		FPS() = default;
		virtual ~FPS() override = default;

		virtual void Update() override;

		int GetFPS() const { return m_FPS; }

		FPS(const FPS& other) = delete;
		FPS(FPS&& other) = delete;
		FPS& operator=(const FPS& other) = delete;
		FPS& operator=(FPS&& other) = delete;

	private:

		bool hasText{ true };

		std::weak_ptr<Text> m_pText{};

		const float m_TimeToUpdate{ 0.1f };

		float m_ResetTimer{};

		int m_FPS{};

	};
}


