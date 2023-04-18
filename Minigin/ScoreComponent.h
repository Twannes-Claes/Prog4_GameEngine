#pragma once
#include "BaseComponent.h"

class GameObject;

namespace Monke
{
	class ScoreComponent final : public BaseComponent
	{
	public:

		explicit ScoreComponent(GameObject* parent);
		virtual ~ScoreComponent() override = default;

		virtual void Initialize() override {}

		void SetScore(const float Score) { m_Score = Score; }

		void Reset() { m_Score = 0; }

		void AddScore(const float amount) { m_Score += amount; }

		float& GetScore() { return m_Score; }

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

	private:

		float m_Score{};
	};
}

