#pragma once
#include "BaseComponent.h"
#include "Observer.h"

namespace Monke
{
	class HealthComponent;
	class Text;

	class LivesDisplay final : public BaseComponent, public Observer<HealthComponent>
	{
	public:

		explicit LivesDisplay(GameObject* parent);
		virtual ~LivesDisplay() override = default;

		virtual void Initialize() override;

		void SetHealthComponent(HealthComponent* pHealthComponent) { m_pHealthComp = pHealthComponent; }

		virtual void Notify(const unsigned eventID, HealthComponent* object) override;

		LivesDisplay(const LivesDisplay& other) = delete;
		LivesDisplay(LivesDisplay&& other) = delete;
		LivesDisplay& operator=(const LivesDisplay& other) = delete;
		LivesDisplay& operator=(LivesDisplay&& other) = delete;

	private:

		void SetDisplayText(const int amountLives) const;

		Text* m_pTextComp{};

		HealthComponent* m_pHealthComp{};
	};
}

