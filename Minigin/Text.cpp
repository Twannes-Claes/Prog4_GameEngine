#include <stdexcept>
#include <SDL_ttf.h>
#include "Text.h"
#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "Transform.h"
#include "Errors.h"
#include "Texture.h"

namespace Monke
{
	Text::Text(std::weak_ptr<GameObject> parent)
	:UpdateComponent(parent)
	{
	}

	void Text::Initialize()
	{

		//todo : make this a function

		const auto pOwner{ GetOwner().lock() };

		m_pTransformComp = pOwner->GetComponent<Transform>();
		
		if (m_pTransformComp.expired())
		{
			const auto error = Expired_Weak_Ptr(__FILE__, __LINE__, "No transform component to draw on a given position");
		}

		m_pTextureComp = pOwner->GetComponent<Texture>();

		if (m_pTextureComp.expired())
		{
			m_pTextureComp = pOwner->AddComponent<Texture>();
		}
		
	}

	void Text::Update()
	{
		if (m_NeedsUpdate == false || m_pTextureComp.expired()) return;

		ChangeTextTexture();

		m_pTextureComp.lock()->SetTexture(m_pTextTexture);
	}

	void Text::ChangeTextTexture()
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}




