

#include "GameObject.h"
#include "Text.h"
#include "FPS.h"
#include "Time.h"
#include "Errors.h"

namespace  Monke
{
	FPS::FPS(std::weak_ptr<GameObject> parent)
	:UpdateComponent(parent)
	{
	}

	void FPS::Initialize()
	{

		m_pText = GetOwner().lock()->GetComponent<Text>();
		
		if (m_pText.expired())
		{
			const auto error = Expired_Weak_Ptr(__FILE__, __LINE__, "No text component found to display FPS as text");
		}

		//GetComponentCheck(m_pText, "No text component found to display FPS as text");
		
	}

	void FPS::Update()
	{
		//get deltatime
		const float deltaTime{ Time::GetInstance().GetElapsed() };

		//calculate timer and check if updatetime has been hit
		m_ResetTimer += deltaTime;

		if(m_ResetTimer >= m_TimeToUpdate)
		{
			m_ResetTimer -= m_TimeToUpdate;

			//calculate fps
			m_FPS = static_cast<int>(1.0f / deltaTime);

			//check if m_pText is valid
			if (m_pText.expired()) return;

			//make stream to pass onto textcomponent
			m_StreamFPS << m_FPS;

			if (m_FPS < 1000) m_StreamFPS << ' ';

			m_StreamFPS << " FPS";

			//set the text to the fps counter
			m_pText.lock()->SetText(m_StreamFPS.str());

			//clear the stringstream
			m_StreamFPS.str("");
		}
	}
}
