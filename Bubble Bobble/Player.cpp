#include "Player.h"

#include "AnimationTexture.h"
#include "GameObject.h"
#include "ResourceManager.h"

namespace Monke
{
	Player::Player(GameObject* pParent, int playerIndex)
	:BaseComponent(pParent)
	{
		const auto pTexture = ResourceManager::Get().LoadTexture("Player/Player" + std::to_string(playerIndex) + "_Walk.png");

		GetOwner()->AddComponent<AnimationTexture>(pTexture, 4, 1, 8);
	}
}


