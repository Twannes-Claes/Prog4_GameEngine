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
				m_pTransform = m_pParent.lock()->GetComponent<Transform>();

				if(m_pTransform.expired())
				{
					const auto error = Expired_Weak_Ptr(__FILE__, __LINE__);

					Renderer::GetInstance().RenderTexture(*m_pTextTexture, 0, 0);
					return;
				}
			}

			const glm::vec3 pos{ m_pTransform.lock()->GetPosition() };

			Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
		}
	}
}




