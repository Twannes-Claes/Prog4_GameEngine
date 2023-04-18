#pragma once
#include "BaseComponent.h"

namespace Monke
{
	class Text;

	class LivesDisplay final :public BaseComponent
	{
	public:

		explicit LivesDisplay(GameObject* parent);
		virtual ~LivesDisplay() override = default;

		virtual void Initialize() override;

		LivesDisplay(const LivesDisplay& other) = delete;
		LivesDisplay(LivesDisplay&& other) = delete;
		LivesDisplay& operator=(const LivesDisplay& other) = delete;
		LivesDisplay& operator=(LivesDisplay&& other) = delete;

	private:

		void SetDisplayText(const int amountLives) const;

		Text* m_pTextComp{};
	};
}

