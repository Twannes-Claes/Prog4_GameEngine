#include "CommandClasses.h"

#include <iostream>

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
}

