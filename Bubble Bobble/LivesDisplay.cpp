#include "LivesDisplay.h"

#include <sstream>

#include "GameObject.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "Text.h"

#include "Events.h"

namespace Monke
{

	LivesDisplay::LivesDisplay(GameObject* parent, HealthComponent* pHealthComponent)
	:BaseComponent(parent),
	m_pHealthComp(pHealthComponent)
	{
		m_pTextComp = GetOwner()->GetComponent<Text>();

		if (!m_pTextComp)
		{
			m_pTextComp = GetOwner()->AddComponent<Text>(ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 24), "", SDL_Color(255, 255, 255, 255));
		}

		if (m_pHealthComp)
		{
			m_pHealthComp->GetSubject()->AddObserver(this);
			SetDisplayText(m_pHealthComp->GetAmountLives());
		}
	}

	void LivesDisplay::Notify(const unsigned eventID, HealthComponent* object)
	{
		if(eventID == PlayerEvents::Died)
		{
			SetDisplayText(object->GetAmountLives());
		}
	}

	void LivesDisplay::SetDisplayText(const int amountLives) const
	{
		std::stringstream stream{};
		stream << "Lives: ";

		if(m_pHealthComp->IsDead())
		{
			stream << "dead!!!";
		}
		else
		{
			stream << amountLives;
		}

		m_pTextComp->SetText(stream.str());
	}
}


