#include <stdexcept>
#include <SDL_ttf.h>
#include "Text.h"
#include "Font.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Texture2D.h"
#include "RenderComponent.h"
#include "Transform.h"
#include "Errors.h"

namespace Monke
{
	Text::Text(const std::weak_ptr<GameObject>& pParent)
	:
	RenderComponent(pParent),
	//m_Text (std::move(text)),
	//m_pFont(std::move(font)),
	m_pTextTexture(nullptr)
	{
		// todo add addcomponent(transform)
		m_pTransform = pParent.lock()->GetComponent<Transform>();
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
	}

	void Text::Render() const
	{
		if (m_pTextTexture != nullptr)
		{
			if (m_pTransform.expired())
			{
				const auto yes = Expired_Weak_Ptr("Stopped rendering the text;\n");

				Renderer::GetInstance().RenderTexture(*m_pTextTexture, 0, 0);
				return;
			}

			const glm::vec3 pos{ m_pTransform.lock()->GetPosition() };

			Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
		}
	}
}




