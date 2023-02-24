#include "DataComponent.h"

#include <utility>

namespace Monke
{
	DataComponent::DataComponent(const std::weak_ptr<GameObject>& pParent)
	:
	BaseComponent(pParent)
	{}
}
