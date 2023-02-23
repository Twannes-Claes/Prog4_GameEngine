#include "UpdateComponent.h"

namespace Monke
{
	UpdateComponent::UpdateComponent(std::weak_ptr<GameObject>& pParent)
	: BaseComponent(pParent)
	{}
}

