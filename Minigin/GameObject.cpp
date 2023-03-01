#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "UpdateComponent.h"
#include "RenderComponent.h"

namespace Monke
{
	void GameObject::Initialize() const
	{
		for (const auto& pComponent : m_pUpdateComponents)
		{
			pComponent->Initialize();
		}
		for (const auto& pComponent : m_pRenderComponents)
		{
			pComponent->Initialize();
		}
		for (const auto& pComponent : m_pDataComponents)
		{
			pComponent->Initialize();
		}
	}

	void GameObject::Update() const
	{
		for(const auto& pComponent : m_pUpdateComponents)
		{
			pComponent->Update();
		}

	}

	void GameObject::Render() const
	{
		//const auto& pos = m_transform.GetPosition();
		//Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);

		for (const auto& pComponent : m_pRenderComponents)
		{
			pComponent->Render();
		}

	}

	//void GameObject::SetTexture(const std::string& filename)
	//{
	//	//m_texture = ResourceManager::GetInstance().LoadTexture(filename);
	//}
}