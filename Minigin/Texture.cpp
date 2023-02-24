#include "Texture.h"

#include <glm/vec3.hpp>
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"
#include "Errors.h"

namespace Monke
{
	Texture::Texture(const std::weak_ptr<GameObject>& pParent)
	:
	RenderComponent(pParent)
	//m_pTexture(std::move(pTexture))
	{
		m_pTransform = pParent.lock()->GetComponent<Transform>();
	}

	void Texture::Render() const
	{
		if (m_pTexture != nullptr)
		{
			if (m_pTransform.expired())
			{
				const auto yes = Expired_Weak_Ptr(" stop texture");

				//Renderer::GetInstance().RenderTexture(*m_pTexture, 0, 0);
				return;
			}

			const glm::vec3 pos{ m_pTransform.lock()->GetPosition() };

			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
	}

	void Texture::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
	{
		m_pTexture = pTexture;
	}
}
