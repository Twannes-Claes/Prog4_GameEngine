#pragma once
#include "BaseComponent.h"

namespace Monke
{
	class Text;

	class LiveDisplay final :public BaseComponent
	{
	public:

		explicit LiveDisplay(GameObject* parent);
		virtual ~LiveDisplay() override = default;

		virtual void Initialize() override;

		LiveDisplay(const LiveDisplay& other) = delete;
		LiveDisplay(LiveDisplay&& other) = delete;
		LiveDisplay& operator=(const LiveDisplay& other) = delete;
		LiveDisplay& operator=(LiveDisplay&& other) = delete;

	private:

		void SetDisplayText(const float amountHealth) const;

		Text* m_pTextComp{};
	};
}

