#include "ScoreDisplay.h"

#include <sstream>

#include "GameObject.h"
#include "ScoreComponent.h"
#include "ResourceManager.h"
#include "Text.h"

#include "Events.h"
#include "HealthComponent.h"

namespace Monke
{

	ScoreDisplay::ScoreDisplay(GameObject* parent)
	:BaseComponent(parent)
	{}

	void ScoreDisplay::Initialize()
	{
		m_pTextComp = GetOwner()->GetComponent<Text>();

		if (!m_pTextComp)
		{
			m_pTextComp = GetOwner()->AddComponent<Text>();
			m_pTextComp->SetFont(ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 24));
			m_pTextComp->SetText("");
			m_pTextComp->SetColor(255, 255, 255, 255);
		}

		//if (ScoreComponent* pScoreComp = GetOwner()->GetComponent<ScoreComponent>())
		//{
		//	pScoreComp->GetSubject()->AddObserver(this);
		//	SetDisplayText(pScoreComp->GetScore());
		//}

		if(m_pScoreComp)
		{
			m_pScoreComp->GetSubject()->AddObserver(this);
			SetDisplayText(m_pScoreComp->GetScore());
		}

		if(m_pHealthComp)
		{
			m_pHealthComp->GetSubject()->AddObserver(this);
		}

	}

	void ScoreDisplay::Notify(const unsigned eventID, ScoreComponent* object)
	{
		if(eventID == PlayerEvents::Score)
		{
			SetDisplayText(object->GetScore());
		}
	}

	void ScoreDisplay::Notify(const unsigned eventID, HealthComponent*)
	{
		if (eventID == PlayerEvents::Damage)
		{
			m_pScoreComp->AddScore(50);
		}
	}

	void ScoreDisplay::SetDisplayText(const float amountScore) const
	{
		std::stringstream stream{};
		stream << "Score: " << amountScore;

		m_pTextComp->SetText(stream.str());
	}
}



