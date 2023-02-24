#include "Transform.h"

#include <utility>

namespace Monke
{
	Transform::Transform(const std::weak_ptr<GameObject>& pParent)
	:
	DataComponent(pParent)
	//m_Position(pos)
	{}
}
