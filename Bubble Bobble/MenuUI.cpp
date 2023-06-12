#include "MenuUI.h"

#include <SDL_keycode.h>

#include "GameObject.h"
#include "ResourceManager.h"
#include "Transform.h"

#include "AnimationTexture.h"
#include "CommandClasses.h"
#include "FPS.h"
#include "InputManager.h"
#include "Texture.h"

namespace Monke
{
	MenuUI::MenuUI(GameObject* pParent) :BaseComponent(pParent)
	{
		GetOwner()->GetTransform()->SetPosition(125, 25);

		m_pLogo = GetOwner()->AddComponent<AnimationTexture>(ResourceManager::Get().LoadTexture("HUD/Logo.png"), 6, 1, 6);

		const auto textGamemode = GetOwner()->AddCreateChild();

		textGamemode->GetTransform()->SetPosition(60, 550);

		textGamemode->AddComponent<Texture>(ResourceManager::Get().LoadTexture("HUD/Gamemodes.png"));

		InputManager::Get().AddCommand(SDLK_LEFT, InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(0, 1));
		InputManager::Get().AddCommand(SDLK_UP, InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(0, 2));
		InputManager::Get().AddCommand(SDLK_RIGHT, InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(0, 3));

		InputManager::Get().AddCommand(0,Gamepad::GamepadButton::DPad_Left ,InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(0, 1));
		InputManager::Get().AddCommand(0,Gamepad::GamepadButton::DPad_Up ,InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(0, 2));
		InputManager::Get().AddCommand(0,Gamepad::GamepadButton::Dpad_Right ,InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(0, 3));

		//FPS object
		const auto pFPS=  GetOwner()->AddCreateChild();
		pFPS->GetTransform()->SetPosition(-120, -15);
		pFPS->AddComponent<FPS>(ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 15), SDL_Color(255, 255, 0, 255));

		//const auto pEnable
		//
		//InputManager::Get().AddCommand(SDLK_TAB, InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(0, 3));
	}
}
