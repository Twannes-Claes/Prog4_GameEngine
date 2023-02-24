#include "BaseComponent.h"

namespace Monke
{
	BaseComponent::BaseComponent(const std::weak_ptr<GameObject>& pParent)
	:
	m_pParent{pParent}
	{}
}
