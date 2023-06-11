#include "Player.h"

#include <SDL_keycode.h>

#include "AnimationTexture.h"
#include "CommandClasses.h"
#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Rigidbody.h"

namespace Monke
{
	Player::Player(GameObject* pParent, int playerIndex)
	:BaseComponent(pParent)
	{
		const auto pTexture = ResourceManager::Get().LoadTexture("Player/Player" + std::to_string(playerIndex) + "_Walk.png");

		GetOwner()->AddComponent<AnimationTexture>(pTexture, 4, 1, 8);
		GetOwner()->AddComponent<Rigidbody>(glm::vec2(48, 622), glm::vec2(48, 48));

		if(playerIndex == 1)
		{
			InputManager::Get().AddCommand<MoveCommand>(SDLK_w, SDLK_d, SDLK_s, SDLK_a, std::make_unique<MoveCommand>(GetOwner(), 150.f));
		}
		else
		{
			InputManager::Get().AddCommand<MoveCommand>(0, Gamepad::GamepadButton::DPad_Up, Gamepad::GamepadButton::Dpad_Right, Gamepad::GamepadButton::DPad_Down, Gamepad::GamepadButton::DPad_Left, std::make_unique<MoveCommand>(GetOwner(), 150.f));
		}
	}
}


