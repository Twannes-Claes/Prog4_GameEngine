
#include <utility>
#include "GameObject.h"
#include "Text.h"
#include "FPS.h"
#include "Time.h"

namespace  Monke
{
	FPS::FPS(const std::weak_ptr<GameObject>& pParent)
	:
	UpdateComponent(pParent)
	{
		//todo: move add component(Text) in the FPS
		m_pText = pParent.lock()->GetComponent<Text>();
	}

	void FPS::Update()
	{
		

		const float deltaTime{ Time::GetInstance().GetElapsed() };

		m_ResetTimer += deltaTime;

		if(m_ResetTimer >= m_TimeToUpdate)
		{
			m_ResetTimer -= m_TimeToUpdate;

			m_FPS = static_cast<int>(1.0f / deltaTime);

			std::stringstream fps{};

			fps << m_FPS;
			if (m_FPS < 1000) fps << ' ';
			fps << " FPS";

			if (m_pText.expired())
			{
				return;
			}

			m_pText.lock()->SetText(fps.str());

		}
	}
}
