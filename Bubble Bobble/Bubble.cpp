#include "Bubble.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "Timer.h"

#include "AnimationTexture.h"
#include "Transform.h"

namespace Monke
{
	Bubble::Bubble(GameObject* pParent, const glm::vec2)
	:BaseComponent(pParent)
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
			GetOwner()->Destroy();
		}
	}
}


