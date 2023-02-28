
#include <utility>
#include "GameObject.h"
#include "Text.h"
#include "FPS.h"
#include "Time.h"
#include "Errors.h"

namespace  Monke
{
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

			if(hasText)
			{
				if (m_pText.expired())
				{
					m_pText = GetParent().lock()->GetComponent<Text>();

					if (m_pText.expired())
					{
						const auto error = Expired_Weak_Ptr(__FILE__, __LINE__, "No text component found to display FPS as text");
						hasText = false;
						return;
					}
				}

				m_pText.lock()->SetText(fps.str());
			}


		}
	}
}
