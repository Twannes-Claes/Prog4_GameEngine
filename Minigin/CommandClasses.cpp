#include "CommandClasses.h"

#include <iostream>

#include "GameObject.h"
#include "Timer.h"
#include "Transform.h"

namespace Monke
{
	MoveCommand::MoveCommand(GameObject* object, const float speed)
	:m_pObject(object),
	m_Speed(speed)
	{
		m_pTranform = object->GetComponent<Transform>();
	}

	void MoveCommand::Execute()
	{
		glm::vec2 pos = GetInput() * m_Speed * Timer::Get().GetElapsed();

		pos += m_pTranform->GetLocalPosition();

		m_pTranform->SetLocalPosition(pos.x, pos.y);
	}
}

