#include  "HealthComponent.h"

namespace Monke
{
	HealthComponent::HealthComponent(GameObject* parent)
	:BaseComponent(parent)
	{
	}

	void HealthComponent::Damage(const float damageAmount)
	{
		m_CurrentHealth -= damageAmount;

		//do call to observer

		m_IsDead = CalculateHasDied();

		if(m_IsDead)
		{
			//do call to observer
		}
	}

}


