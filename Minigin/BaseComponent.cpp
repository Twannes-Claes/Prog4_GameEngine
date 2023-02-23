#include "BaseComponent.h"

namespace Monke
{
	BaseComponent::BaseComponent(std::shared_ptr<GameObject>& pParent)
	: m_pParent{ pParent }
	{
	}
}
