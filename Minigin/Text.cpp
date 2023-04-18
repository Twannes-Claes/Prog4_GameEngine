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
	Text::Text(GameObject* parent)
	:BaseComponent(parent)
	{
	}

	void Text::Initialize()
	{

		const auto pOwner{ GetOwner() };

		m_pTransformComp = pOwner->GetComponent<Transform>();

		m_pTextureComp = pOwner->GetComponent<Texture>();

		if(m_pTextureComp == nullptr)
		{
			m_pTextureComp = pOwner->AddComponent<Texture>();
		}
		
	}

	void Text::Update()
	{
		if (m_NeedsUpdate == false || m_pTextureComp == nullptr) return;

		ChangeTextTexture();

		m_pTextureComp->SetTexture(m_pTextTexture);
	}

	void Text::ChangeTextTexture()
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::Get().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTextTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}




