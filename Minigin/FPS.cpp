

#include "GameObject.h"
#include "Text.h"
#include "FPS.h"
#include "Timer.h"
#include "Errors.h"

namespace  Monke
{
	FPS::FPS( GameObject* parent)
	:BaseComponent(parent)
	{
	}

	void FPS::Initialize()
	{
		m_pText = GetOwner()->GetComponent<Text>();
	}

	void FPS::Update()
	{
		//get deltatime
		const float deltaTime{ Timer::Get().GetElapsed() };

		//calculate timer and check if updatetime has been hit
		m_ResetTimer += deltaTime;

		if(m_ResetTimer >= m_TimeToUpdate)
		{
			m_ResetTimer -= m_TimeToUpdate;

			//calculate fps
			m_NewFPS = static_cast<int>(1.0f / deltaTime);

			if (m_NewFPS == m_FPS) return;

			m_FPS = m_NewFPS;

			//check if m_pText is valid
			if (m_pText == nullptr) return;

			//make stream to pass onto textcomponent
			m_StreamFPS << m_FPS;

			if (m_FPS < 1000) m_StreamFPS << ' ';

			m_StreamFPS << " FPS";

			//set the text to the fps counter
			m_pText->SetText(m_StreamFPS.str());

			//clear the stringstream
			m_StreamFPS.str("");
		}
	}
}
