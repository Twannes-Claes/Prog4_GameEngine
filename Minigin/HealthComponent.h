#pragma once

#include "BaseComponent.h"

class GameObject;

namespace Monke
{
	class HealthComponent final : public BaseComponent
	{
	public:

		explicit HealthComponent(GameObject* parent);
		virtual ~HealthComponent() override = default;

		virtual void Initialize() override  {}

		void Damage(const float damageAmount);

		void SetHealth(const float health) { m_CurrentHealth = health; }
		void SetMaxHealth(const float maxHealth) { m_MaxHealth = maxHealth; }

		void Reset() { m_CurrentHealth = m_MaxHealth; }

		float& GetCurrentHealth() { return m_CurrentHealth; }
		float GetMaxHealth() const { return m_MaxHealth; }
		bool IsDead() const { return m_IsDead; }

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

	private:

		bool CalculateHasDied() const { return m_CurrentHealth < 0; }

		float m_MaxHealth{};

		float m_CurrentHealth{};

		bool m_IsDead{ false };

	};
}


