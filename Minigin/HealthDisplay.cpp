#include "HealthDisplay.h"

#include <sstream>

#include "GameObject.h"
#include "HealthComponent.h"
#include "ResourceManager.h"
#include "Text.h"

namespace Monke
{

	HealthDisplay::HealthDisplay(GameObject* parent)
	:BaseComponent(parent)
	{
		m_pTextComp = GetOwner()->GetComponent<Text>();

		if (!m_pTextComp)
		{
			m_pTextComp = GetOwner()->AddComponent<Text>(ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 24), "", SDL_Color(255, 255, 255, 255));
		}

		if (HealthComponent* pHealthComp = GetOwner()->GetComponent<HealthComponent>())
		{
			SetDisplayText(pHealthComp->GetCurrentHealth());
		}
	}

	void HealthDisplay::SetDisplayText(const float amountHealth) const
	{
		std::stringstream stream{};
		stream << "Health: " << amountHealth;

		m_pTextComp->SetText(stream.str());
	}
}


