#pragma once
#include "BaseComponent.h"
#include "Subject.h"
#include "Events.h"

class GameObject;

namespace Monke
{
	class ScoreComponent final : public BaseComponent
	{
	public:

		explicit ScoreComponent(GameObject* parent);
		virtual ~ScoreComponent() override = default;

		virtual void Initialize() override {}

		void SetScore(const float Score) { m_Score = Score; m_Subject->Notify(PlayerEvents::Score, this);}
		void AddScore(const float amount) { m_Score += amount; m_Subject->Notify(PlayerEvents::Score, this);}
		float& GetScore() { return m_Score; }

		void Reset() { m_Score = 0; m_Subject->Notify(PlayerEvents::Score, this); }

		Subject<ScoreComponent>* GetSubject() const { return m_Subject.get(); }

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

	private:

		float m_Score{};

		std::unique_ptr<Subject<ScoreComponent>> m_Subject = std::make_unique<Subject<ScoreComponent>>();
	};
}

