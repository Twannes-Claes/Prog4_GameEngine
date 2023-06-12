#include "Bubble.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "Timer.h"

#include "AnimationTexture.h"
#include "HealthComponent.h"
#include "Transform.h"

namespace Monke
{
	Bubble::Bubble(GameObject* pParent, const glm::vec2, HealthComponent* pHealth)
	:BaseComponent(pParent),
	m_pHealth(pHealth)
	{
		m_pTransform = GetOwner()->GetTransform();

		const auto pTexture = ResourceManager::Get().LoadTexture("Player/Bubble.png");

		m_pTexture = GetOwner()->AddComponent<AnimationTexture>(pTexture, 3, 1, 3);
	}

	void Bubble::Update()
	{
		m_CurrentLifeTime += Timer::Get().GetElapsed();

		if (m_CurrentLifeTime >= m_MaxLifeTime)
		{
			m_pHealth->Damage(100.f);
			GetOwner()->Destroy();
		}
	}
}


