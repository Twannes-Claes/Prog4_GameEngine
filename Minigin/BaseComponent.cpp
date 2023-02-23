#include "BaseComponent.h"

namespace Monke
{
	BaseComponent::BaseComponent(std::weak_ptr<GameObject>& pParent)
	: m_pParent{ pParent }
	{
	}
}
