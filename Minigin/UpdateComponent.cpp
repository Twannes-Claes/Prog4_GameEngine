#include "UpdateComponent.h"

#include <utility>

namespace Monke
{
	UpdateComponent::UpdateComponent(const std::weak_ptr<GameObject>& pParent)
	:
	BaseComponent(pParent)
	{}
}

