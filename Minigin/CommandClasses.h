#pragma once
#include "Command.h"

namespace Monke
{
	class Transform;

	class MoveCommand final : public AxisCommand
	{

	public:

		explicit MoveCommand(GameObject* object, const float speed);
		virtual ~MoveCommand() override = default;

		virtual void Execute() override;

		void SetSpeed(const float speed) { m_Speed = speed; }

		MoveCommand(const MoveCommand&) = delete;
		MoveCommand(MoveCommand&&) = delete;
		MoveCommand& operator= (const MoveCommand&) = delete;
		MoveCommand& operator= (const MoveCommand&&) = delete;

	private:

		GameObject* m_pObject;

		Transform* m_pTranform{};

		float m_Speed{ 10.f };

	};

}

