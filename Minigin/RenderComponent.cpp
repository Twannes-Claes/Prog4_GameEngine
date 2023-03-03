#include "RenderComponent.h"

#include "Transform.h"
//#include "Texture2D.h"
#include "Renderer.h"

namespace Monke
{
	RenderComponent::RenderComponent(std::weak_ptr<GameObject> parent)
	:BaseComponent(parent)
	{
	}

	void RenderComponent::RenderTexture(const std::weak_ptr<Transform>& pTransform, const std::shared_ptr<Texture2D>& pTexture) const
	{
		if (pTexture == nullptr) return;

		if (pTransform.expired())
		{
			Renderer::GetInstance().RenderTexture(*pTexture, m_DefaultDrawPos.x, m_DefaultDrawPos.y);
			return;
		}

		const glm::vec3 pos{ pTransform.lock()->GetWorldPosition() };

		Renderer::GetInstance().RenderTexture(*pTexture, pos.x, pos.y);
	}
}
