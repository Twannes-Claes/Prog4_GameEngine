#include "Transform.h"

#include "GameObject.h"

namespace Monke
{
	Transform::Transform(std::weak_ptr<GameObject> parent)
	:BaseComponent(parent)
	{
	}

	void Transform::Initialize()
	{
		
	}

	const glm::vec3& Transform::GetWorldPosition()
	{
		if (m_IsDirty)
		{
			UpdateWorldPosition();
		}
		return m_WorldPosition;
	}

	void Transform::SetTransformDirty()
	{
		//todo: maybe cache this with initialize function but changing parent will break that
		const auto vChildren = GetOwner().lock()->GetAllChildren();

		for ( const auto& child : vChildren)
		{
			auto transformComp = child.lock()->GetComponent<Transform>();

			if (transformComp.expired())
			{
				continue;
			}

			transformComp.lock()->SetTransformDirty();
		}

		m_IsDirty = true;
	}

	void Transform::UpdateWorldPosition()
	{
		if (const auto OwnerParent{ GetOwner().lock()->GetParent() }; OwnerParent.expired())
		{
			m_WorldPosition = m_LocalPosition;
		}
		else
		{
			const auto transformParentComp = OwnerParent.lock()->GetComponent<Transform>().lock();
			m_WorldPosition = transformParentComp->GetWorldPosition() + m_LocalPosition;
		}

		m_IsDirty = false;
	}
}
