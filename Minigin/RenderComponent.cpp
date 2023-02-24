#include "RenderComponent.h"

#include <utility>

namespace Monke
{
	RenderComponent::RenderComponent(const std::weak_ptr<GameObject>& pParent)
	:
	BaseComponent(pParent)
	{}
}
