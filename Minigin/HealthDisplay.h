#pragma once
#include "BaseComponent.h"

namespace Monke
{
	class Text;

	class HealthDisplay final :public BaseComponent
	{
	public:

		explicit HealthDisplay(GameObject* parent);
		virtual ~HealthDisplay() override = default;

		HealthDisplay(const HealthDisplay& other) = delete;
		HealthDisplay(HealthDisplay&& other) = delete;
		HealthDisplay& operator=(const HealthDisplay& other) = delete;
		HealthDisplay& operator=(HealthDisplay&& other) = delete;

	private:

		void SetDisplayText(const float amountHealth) const;

		Text* m_pTextComp{};
	};
}

