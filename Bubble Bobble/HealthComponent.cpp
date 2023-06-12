#include  "HealthComponent.h"

#include "GameObject.h"
#include "MenuUI.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ServiceLocator.h"

namespace Monke
{
	HealthComponent::HealthComponent(GameObject* parent, float maxHealth, int amountLives)
	:BaseComponent(parent)
	{
		SetMaxHealth(maxHealth);
		SetAmountLives(amountLives);

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

			//GetOwner()->Destroy();
			//
			//const auto scene = SceneManager::Get().AddCreateScene("MainMenu");
			//
			//const auto pLevelLoader{ scene->MakeGameObject() };
			//pLevelLoader->AddComponent<MenuUI>();
		}
	}

	bool HealthComponent::CalculateHasDied()
	{
		if (m_CurrentHealth > 0) return false;

		if(m_AmountOfLives > 0)
		{
			ServiceLocator::GetSoundSystem().Play(0, "Sounds/Jump.wav", 0.5f);
			--m_AmountOfLives;
			Reset();

			m_Subject->Notify(PlayerEvents::Died, this);
		}
		else
		{
			ServiceLocator::GetSoundSystem().Play(1, "Sounds/Jump_Bubble.wav", 0.5f);

			return true;
		}

		return false;
	}
}


