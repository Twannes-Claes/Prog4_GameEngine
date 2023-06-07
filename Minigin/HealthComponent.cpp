#include  "HealthComponent.h"

#include "ServiceLocator.h"

namespace Monke
{
	HealthComponent::HealthComponent(GameObject* parent)
	:BaseComponent(parent)
	{
	}

	void HealthComponent::Initialize()
	{
		Reset();
	}

	void HealthComponent::Damage(const float damageAmount)
	{
		if (m_IsDead) return;

		m_CurrentHealth -= damageAmount;

		m_Subject->Notify(PlayerEvents::Damage, this);

		m_IsDead = CalculateHasDied();

		if(m_IsDead)
		{
			m_Subject->Notify(PlayerEvents::Died, this);
		}
	}

	bool HealthComponent::CalculateHasDied()
	{
		if (m_CurrentHealth > 0) return false;

		if(m_AmountOfLives > 0)
		{
			ServiceLocator::GetSoundSystem().Play(0, "Sounds/Jump.wav", 100.f);
			--m_AmountOfLives;
			Reset();

			m_Subject->Notify(PlayerEvents::Died, this);
		}
		else
		{
			return true;
		}

		return false;
	}
}


