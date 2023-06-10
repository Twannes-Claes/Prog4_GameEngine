#pragma once

#include "BaseComponent.h"
#include "Observer.h"

namespace Monke
{
	class HealthComponent;
	class ScoreComponent;
	class Text;

	class ScoreDisplay :public BaseComponent, public Observer<ScoreComponent>, public Observer<HealthComponent>
	{
	public:

		explicit ScoreDisplay(GameObject* parent, ScoreComponent* pScoreComponent, HealthComponent* pHealthComponent);
		virtual ~ScoreDisplay() override = default;

		virtual void Notify(const unsigned eventID, ScoreComponent* object) override;
		virtual void Notify(const unsigned eventID, HealthComponent* object) override;

		ScoreDisplay(const ScoreDisplay& other) = delete;
		ScoreDisplay(ScoreDisplay&& other) = delete;
		ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
		ScoreDisplay& operator=(ScoreDisplay&& other) = delete;

	private:

		void SetDisplayText(const float amountScore) const;

		Text* m_pTextComp{};

		ScoreComponent* m_pScoreComp{};
		HealthComponent* m_pHealthComp{};
	};
}

