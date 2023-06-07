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

		ServiceLocator::GetSoundSystem().LoadSound(0, "Sounds/Jump.wav");
		ServiceLocator::GetSoundSystem().LoadSound(1, "Sounds/Jump_Bubble.wav");
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
			ServiceLocator::GetSoundSystem().Play(0, 1.f);
			--m_AmountOfLives;
			Reset();

			m_Subject->Notify(PlayerEvents::Died, this);
		}
		else
		{
			ServiceLocator::GetSoundSystem().Play(1, 1.f);
			return true;
		}

		return false;
	}
}


