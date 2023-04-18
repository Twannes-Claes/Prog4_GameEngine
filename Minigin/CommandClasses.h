#pragma once
#include "Command.h"

namespace Monke
{
	class ScoreComponent;
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

	class ScoreCommand final : public Command
	{

	public:
		explicit ScoreCommand(ScoreComponent* object, const float score);
		virtual ~ScoreCommand() override = default;

		virtual void Execute() override;

		ScoreCommand(const ScoreCommand&) = delete;
		ScoreCommand(ScoreCommand&&) = delete;
		ScoreCommand& operator= (const ScoreCommand&) = delete;
		ScoreCommand& operator= (const ScoreCommand&&) = delete;

	private:

		ScoreComponent* m_pScore;

		const float m_ScoreToAdd;
	};

}

