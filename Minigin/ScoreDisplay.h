#pragma once

#include "BaseComponent.h"

namespace Monke
{
	class Text;

	class ScoreDisplay final :public BaseComponent
	{
	public:

		explicit ScoreDisplay(GameObject* parent);
		virtual ~ScoreDisplay() override = default;

		virtual void Initialize() override;

		ScoreDisplay(const ScoreDisplay& other) = delete;
		ScoreDisplay(ScoreDisplay&& other) = delete;
		ScoreDisplay& operator=(const ScoreDisplay& other) = delete;
		ScoreDisplay& operator=(ScoreDisplay&& other) = delete;

	private:

		void SetDisplayText(const float amountScore) const;

		Text* m_pTextComp{};
	};
}

