#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "UpdateComponent.h"
#include "RenderComponent.h"
#include "Transform.h"

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

	void GameObject::Update()
	{
		for(const auto& pComponent : m_pUpdateComponents)
		{
			pComponent->Update();
		}

		CleanUpVector(m_pUpdateComponents);
		CleanUpVector(m_pRenderComponents);
		CleanUpVector(m_pDataComponents);

	}

	void GameObject::Render() const
	{

		for (const auto& pComponent : m_pRenderComponents)
		{
			pComponent->Render();
		}

	}

	void GameObject::SetParent(const std::weak_ptr<GameObject>& newParent, const bool keepWorldPosition)
	{
		//lock/chache the parent
		const auto originalParent{ m_pParent.lock()};

		//Remove itself as a child from the previous parent (if any)
		if (m_pParent.expired() == false)
		{
			//chech if parents are not the same
			if (originalParent == newParent.lock()) return;

			m_pParent.lock()->RemoveChild(weak_from_this());
		}
		else
		{
			if (newParent.expired()) return;
		}

		//Set the given parent on itself
		m_pParent = newParent;

		//Add itself as a child to the given parent
		if (m_pParent.expired() == false)
		{
			m_pParent.lock()->m_pChildren.push_back(weak_from_this());
		}

		//get transform component
		const auto transformComp = GetComponent<Transform>();

		//if no transform has been found return
		if (transformComp.expired()) return;

		//lock the transform
		const auto ltransform = transformComp.lock();

		//if no parent set local as world position
		if(m_pParent.expired())
		{
			ltransform->SetLocalPosition(ltransform->GetWorldPosition());
		}
		else
		{
			if (keepWorldPosition)
			{
				// Set the local position to be the difference between the local position and worlposition
				ltransform->SetLocalPosition(ltransform->GetLocalPosition() - newParent.lock()->GetComponent<Transform>().lock()->GetWorldPosition());
			}

			// Mark the transform as dirty, indicating that it has been modified
			ltransform->SetTransformDirty();
		}

	}

	void GameObject::AddChild(const std::weak_ptr<GameObject>& child)
	{

		//cache the lock
		const auto lChild{ child.lock() };
		
		//Remove the given child from the child's previous parent
		if(lChild->m_pParent.expired() == false)
		{
			lChild->m_pParent.lock()->RemoveChild(child);
		}

		//Set itself as parent of the child

		lChild->SetParent(weak_from_this(), false);

		//Add the child to its children list
		m_pChildren.push_back(child);
	}

	void GameObject::RemoveChild(std::weak_ptr<GameObject> child)
	{
		//find the child that matches the child in the vector
		//if a child has been found erase it
		if (const auto it = std::remove_if(m_pChildren.begin(), m_pChildren.end(), 
	    [&child]
	    (const std::weak_ptr<GameObject>& object)
	    {
	        //return if has found the child
	        return object.lock() == child.lock();
	    
	    }); it != m_pChildren.end())
		{
			//set the parent to an empty gameobject
			//(*it).lock()->SetParent(std::weak_ptr<GameObject>(), true);
			(*it).lock()->m_pParent = std::weak_ptr<GameObject>();
			m_pChildren.erase(it);
		}
	}

	void GameObject::Destroy()
	{
		//set marked as dead
		m_IsMarkedDead = true;

		//Destroy all children
		for (const auto& child : m_pChildren)
		{
			if (child.expired()) continue;
			//mark all other children as dead
			child.lock()->Destroy();
		}
	}
}
