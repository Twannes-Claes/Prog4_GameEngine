#include "CommandClasses.h"

#include <iostream>

#include "GameObject.h"
#include "Time.h"
#include "Transform.h"

namespace Monke
{
	MoveCommand::MoveCommand(GameObject* object)
	:m_pObject(object)
	{
		m_pTranform = object->GetComponent<Transform>();
	}

	void MoveCommand::Execute()
	{
		glm::vec2 pos = GetInput() * m_Speed * Time::GetInstance().GetElapsed();

		pos += static_cast<glm::vec2>(m_pTranform.lock()->GetLocalPosition());

		m_pTranform.lock()->SetLocalPosition(pos.x, pos.y);
	}
}

