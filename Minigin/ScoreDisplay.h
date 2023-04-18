#pragma once

#include "BaseComponent.h"
#include "Observer.h"

namespace Monke
{
	class ScoreComponent;
	class Text;

	class ScoreDisplay :public BaseComponent, public Observer<ScoreComponent>
	{
	public:

		explicit ScoreDisplay(GameObject* parent);
		virtual ~ScoreDisplay() override = default;

		virtual void Initialize() override;

		virtual void Notify(const unsigned eventID, ScoreComponent* object) override;

		void SetScoreComponent(ScoreComponent* scoreCompont) { m_pScoreComp = scoreCompont; }

		ScoreDisplay(const ScoreDisplay& other) = delete;
		ScoreDisplay(ScoreDisplay&& other) = delete;
		ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
		ScoreDisplay& operator=(ScoreDisplay&& other) = delete;

	private:

		void SetDisplayText(const float amountScore) const;

		Text* m_pTextComp{};

		ScoreComponent* m_pScoreComp{};
	};
}

