#include "Transform.h"

#include "GameObject.h"

namespace Monke
{
	Transform::Transform(GameObject* parent)
	:BaseComponent(parent)
	{
	}

	void Transform::Initialize()
	{
		
	}

	const glm::vec2& Transform::GetWorldPosition()
	{
		if (m_IsDirty)
		{
			UpdateWorldPosition();
		}
		return m_WorldPosition;
	}

	void Transform::SetTransformDirty()
	{
		for (const auto vChildren = GetOwner()->GetAllChildren(); const auto& child : vChildren)
		{
			const auto transformComp = child->GetComponent<Transform>();

			transformComp->SetTransformDirty();
		}

		m_IsDirty = true;
	}

	void Transform::UpdateWorldPosition()
	{
		if (const auto OwnerParent{ GetOwner()->GetParent() }; OwnerParent == nullptr)
		{
			m_WorldPosition = m_LocalPosition;
		}
		else
		{
			const auto transformParentComp = OwnerParent->GetComponent<Transform>();
			m_WorldPosition = transformParentComp->GetWorldPosition() + m_LocalPosition;
		}

		m_IsDirty = false;
	}
}
