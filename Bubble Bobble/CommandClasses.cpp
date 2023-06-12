#include "CommandClasses.h"

#include <iostream>

#include "Bubble.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "InputManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ScoreComponent.h"
#include "Timer.h"
#include "Transform.h"

#include "Level.h"
#include "MenuUI.h"
#include "Rigidbody.h"
#include "ServiceLocator.h"

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
		const float displacement = GetInput().x * m_Speed * Timer::Get().GetElapsed();

		m_pTranform->SetLocalPosition(m_pTranform->GetLocalPosition().x + displacement, m_pTranform->GetLocalPosition().y);
	}

	ScoreCommand::ScoreCommand(ScoreComponent* object, const float score)
	:m_ScoreToAdd(score)
	{
		m_pScore = object;
	}

	void ScoreCommand::Execute()
	{
		m_pScore->AddScore(m_ScoreToAdd);
	}

	DamageCommand::DamageCommand(HealthComponent* object, const float damageAmount)
	:m_DamageAmount(damageAmount)
	{
		m_pHealthComp = object;
	}

	void DamageCommand::Execute()
	{
		m_pHealthComp->Damage(m_DamageAmount);
	}

	void SwitchSceneCommand::Execute()
	{
		int newLevelID = m_LevelID + 1;
		
		if (newLevelID > 3)
		{
			ServiceLocator::GetSoundSystem().StopAll();
			const auto scene = SceneManager::Get().AddCreateScene("MainMenu");

			const auto pLevelLoader{ scene->MakeGameObject() };
			pLevelLoader->AddComponent<MenuUI>();

			return;
		}

		const int newGameMode = m_Gamemode;

		const auto scene = SceneManager::Get().AddCreateScene("Level" + std::to_string(newLevelID));
		
		const auto pLevelLoader{ scene->MakeGameObject() };

		pLevelLoader->AddComponent<Level>(newLevelID, newGameMode);
	}

	void JumpCommand::Execute()
	{
		if(m_pRigid->CanJump())
		{
			m_pRigid->AddVelocityY(m_JumpSpeed);
		}
	}

	void BubbleShootCommand::Execute()
	{
		if (m_pHealth->IsDead()) return;;

		const auto newOBject = m_pObject->AddCreateChild();

		newOBject->AddComponent<Bubble>(m_pObject->GetTransform()->GetWorldPosition(), m_pHealth);

		newOBject->SetParent(nullptr);

		ServiceLocator::GetSoundSystem().Play(3, "Sounds/Shoot.wav", 0.5f);
	}

	void MuteCommand::Execute()
	{
		m_Mute = !m_Mute;

		ServiceLocator::GetSoundSystem().Mute(m_Mute);
	}
}

