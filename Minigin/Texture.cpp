#include "Texture.h"

#include <glm/vec3.hpp>
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"
#include "Errors.h"

namespace Monke
{
	Texture::Texture(GameObject* parent)
	:BaseComponent(parent)
	{
	}

	void Texture::Initialize()
	{
		m_pTransform = GetOwner()->GetComponent<Transform>();
	}

	void Texture::Render() const
	{
		if (m_pTexture == nullptr) return;

		const glm::vec2 pos{ m_pTransform->GetWorldPosition() };

		Renderer::Get().RenderTexture(*m_pTexture, pos.x, pos.y);
	}

	void Texture::SetTexture(const std::shared_ptr<Texture2D>& pTexture)
	{
		m_pTexture = pTexture;
	}
}
