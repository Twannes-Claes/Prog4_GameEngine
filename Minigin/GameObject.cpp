#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"

namespace Monke
{

	GameObject::GameObject()
	{
		m_pTransform = AddComponent<Transform>();
	}

	void GameObject::Initialize() const
	{
		//i added a normal for loop over a range based for loop

		//because in my initialize functions in my comnponents i can check if certain components dont exist, if not add the component

		//but adding the component doesnt increase the range of the ranged based for loop, hence why the normal for loop

		for(int i{}; i < static_cast<int>(m_pComponents.size()); ++i)
		{
			m_pComponents[i]->Initialize();
		}
	}

	void GameObject::Update()
	{
		for (int i{}; i < static_cast<int>(m_pComponents.size()); ++i)
		{
			m_pComponents[i]->Update();
		}

		CleanUpVector(m_pComponents);
	}

	void GameObject::Render() const
	{

		for (const auto& pComponent : m_pComponents)
		{
			pComponent->Render();
		}

	}

	void GameObject::OnGUI()
	{
		for (const auto& pComponent : m_pComponents)
		{
			pComponent->OnGUI();
		}
	}

	void GameObject::SetParent(GameObject* newParent, const bool keepWorldPosition)
	{
		////lock/chache the parent
		//const auto originalParent{ m_pParent.lock()};
		//
		////Remove itself as a child from the previous parent (if any)
		//if (m_pParent.expired() == false)
		//{
		//	//chech if parents are not the same
		//	if (originalParent == newParent.lock()) return;
		//
		//	m_pParent.lock()->RemoveChild(weak_from_this());
		//}
		//else
		//{
		//	if (newParent.expired()) return;
		//}
		//
		////Set the given parent on itself
		//m_pParent = newParent;
		//
		////Add itself as a child to the given parent
		//if (m_pParent.expired() == false)
		//{
		//	m_pParent.lock()->m_pChildren.push_back(weak_from_this());
		//}
		//
		////get transform component
		//const auto transformComp = GetComponent<Transform>();
		//
		////if no transform has been found return
		//if (transformComp.expired()) return;
		//
		////lock the transform
		//const auto ltransform = transformComp.lock();
		//
		////if no parent set local as world position
		//if(m_pParent.expired())
		//{
		//	ltransform->SetLocalPosition(ltransform->GetWorldPosition());
		//}
		//else
		//{
		//	if (keepWorldPosition)
		//	{
		//		// Set the local position to be the difference between the local position and worlposition
		//		ltransform->SetLocalPosition(ltransform->GetLocalPosition() - newParent.lock()->GetComponent<Transform>().lock()->GetWorldPosition());
		//	}
		//
		//	// Mark the transform as dirty, indicating that it has been modified
		//	ltransform->SetTransformDirty();
		//}

		if (newParent == nullptr)
		{
			GetTransform()->SetPosition(GetTransform()->GetWorldPosition());
		}
		else
		{
			if (keepWorldPosition)
			{
				GetTransform()->SetPosition(GetTransform()->GetWorldPosition() - GetParent()->GetTransform()->GetWorldPosition());
			}

			GetTransform()->SetTransformDirty();
		}

		GameObject* child{ nullptr };

		if (m_pParent != nullptr)
		{
			auto& children = m_pParent->m_pChildren;
			if (const auto it = std::ranges::find_if(children, [this](const GameObject* check) 
			{
				return check == this;
			}); 
			it != children.end())
			{
				child = *it;

				children.erase(it);
			}
		}
			
		m_pParent = newParent;

		if (m_pParent != nullptr)
		{
			if (child == nullptr)
			{
				child = this;
			}

			m_pParent->m_pChildren.emplace_back(child);
		}

	}

	void GameObject::Destroy()
	{
		//set marked as dead
		m_IsMarkedDead = true;

		//Destroy all children
		for (const auto& child : m_pChildren)
		{
			child->Destroy();
		}
	}

}
