#include "BaseComponent.h"

namespace Monke
{
	BaseComponent::BaseComponent( std::weak_ptr<GameObject> parent)
	:m_pParent(parent)
	{
	}
}
