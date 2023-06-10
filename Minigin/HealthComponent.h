#pragma once

#include "BaseComponent.h"
#include "Subject.h"
#include "Events.h"


namespace Monke
{

	class HealthComponent final : public BaseComponent
	{
	public:

		explicit HealthComponent(GameObject* parent, float maxHealth, int amountLives);
		virtual ~HealthComponent() override = default;

		void Damage(const float damageAmount);

		void SetHealth(const float health) { m_CurrentHealth = health; m_Subject->Notify(PlayerEvents::Health, this); }
		void SetMaxHealth(const float maxHealth) { m_MaxHealth = maxHealth; m_Subject->Notify(PlayerEvents::Health, this); }
		void SetAmountLives(const int amount) { m_AmountOfLives = amount; m_Subject->Notify(PlayerEvents::Health, this); }

		void Reset() { m_CurrentHealth = m_MaxHealth; m_Subject->Notify(PlayerEvents::Health, this); }

		float& GetCurrentHealth() { return m_CurrentHealth; }
		float GetMaxHealth() const { return m_MaxHealth; }
		int GetAmountLives() const { return m_AmountOfLives; }

		bool IsDead() const { return m_IsDead; }

		Subject<HealthComponent>* GetSubject() const { return m_Subject.get(); }

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

	private:

		bool CalculateHasDied();

		float m_MaxHealth{};

		float m_CurrentHealth{};

		int m_AmountOfLives{};

		bool m_IsDead{ false };

		std::unique_ptr<Subject<HealthComponent>> m_Subject = std::make_unique<Subject<HealthComponent>>();

	};
}


