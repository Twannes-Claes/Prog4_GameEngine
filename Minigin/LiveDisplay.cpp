#include "LiveDisplay.h"

#include <sstream>

#include "GameObject.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "Text.h"

namespace Monke
{

	LiveDisplay::LiveDisplay(GameObject* parent)
	:BaseComponent(parent)
	{}

	void LiveDisplay::Initialize()
	{
		m_pTextComp = GetOwner()->GetComponent<Text>();

		if(!m_pTextComp)
		{
			m_pTextComp = GetOwner()->AddComponent<Text>();
			m_pTextComp->SetFont(ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 24));
			m_pTextComp->SetText("");
			m_pTextComp->SetColor(255,255, 255, 255);
		}

		if(HealthComponent* pHealthComp = GetOwner()->GetComponent<HealthComponent>())
		{
			SetDisplayText(pHealthComp->GetCurrentHealth());
		}
	}

	void LiveDisplay::SetDisplayText(const float amountHealth) const
	{
		std::stringstream stream{};
		stream << "Lives: " << amountHealth;

		m_pTextComp->SetText(stream.str());
	}
}


