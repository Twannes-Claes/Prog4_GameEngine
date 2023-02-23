#include "RenderComponent.h"

namespace Monke
{
	RenderComponent::RenderComponent(std::weak_ptr<GameObject>& pParent)
	: BaseComponent(pParent)
	{}
}
