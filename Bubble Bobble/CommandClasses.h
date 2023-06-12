#pragma once
#include <string>

#include "Command.h"

namespace Monke
{
	class Rigidbody;
	class Scene;
	class HealthComponent;
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

	class DamageCommand final : public Command
	{

	public:

		explicit DamageCommand(HealthComponent* object, const float damageAmount);
		virtual ~DamageCommand() override = default;

		virtual void Execute() override;

		DamageCommand(const ScoreCommand&) = delete;
		DamageCommand(DamageCommand&&) = delete;
		DamageCommand& operator= (const DamageCommand&) = delete;
		DamageCommand& operator= (const DamageCommand&&) = delete;

	private:

		HealthComponent* m_pHealthComp;

		const float m_DamageAmount;
	};

	class SwitchSceneCommand final : public Command
	{
	public:

		explicit SwitchSceneCommand(const int levelID, const int gamemode):m_LevelID(levelID),m_Gamemode(gamemode){}
		virtual ~SwitchSceneCommand() override = default;

		virtual void Execute() override;

		SwitchSceneCommand(const SwitchSceneCommand&) = delete;
		SwitchSceneCommand(SwitchSceneCommand&&) = delete;
		SwitchSceneCommand& operator= (const SwitchSceneCommand&) = delete;
		SwitchSceneCommand& operator= (const SwitchSceneCommand&&) = delete;

	private:

		const int m_LevelID{};
		const int m_Gamemode{};
	};

	class JumpCommand final : public Command
	{
	public:

		explicit JumpCommand(const float jumpSpeed, Rigidbody* pRigid) :m_pRigid(pRigid), m_JumpSpeed(jumpSpeed){}
		virtual ~JumpCommand() override = default;

		virtual void Execute() override;

		JumpCommand(const JumpCommand&) = delete;
		JumpCommand(JumpCommand&&) = delete;
		JumpCommand& operator= (const JumpCommand&) = delete;
		JumpCommand& operator= (const JumpCommand&&) = delete;

	private:

		Rigidbody* m_pRigid{};

		const float m_JumpSpeed{};
	};

	class BubbleShootCommand final : public Command
	{
	public:

		explicit BubbleShootCommand(GameObject* object, HealthComponent* pHealth):m_pObject(object), m_pHealth(pHealth) {}
		virtual ~BubbleShootCommand() override = default;

		virtual void Execute() override;

		BubbleShootCommand(const BubbleShootCommand&) = delete;
		BubbleShootCommand(BubbleShootCommand&&) = delete;
		BubbleShootCommand& operator= (const BubbleShootCommand&) = delete;
		BubbleShootCommand& operator= (const BubbleShootCommand&&) = delete;

	private:

		GameObject* m_pObject{};

		HealthComponent* m_pHealth{};
	};

}

