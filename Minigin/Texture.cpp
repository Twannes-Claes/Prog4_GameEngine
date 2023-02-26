#include "Texture.h"

#include <glm/vec3.hpp>
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"
#include "Errors.h"

namespace Monke
{
	void Texture::Render() const
	{
		if (m_pTexture == nullptr) return;

		if (m_pTransform.expired())
		{
			m_pTransform = m_pParent.lock()->GetComponent<Transform>();

			if(m_pTransform.expired())
			{
				const auto error = Expired_Weak_Ptr(__FILE__, __LINE__, "No transform component to draw on a given position");

				Renderer::GetInstance().RenderTexture(*m_pTexture, 0, 0);
				return;
			}
		}

		const glm::vec3 pos{ m_pTransform.lock()->GetPosition() };

		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
	}

	void Texture::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
	{
		m_pTexture = pTexture;
	}
}
