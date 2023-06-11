#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <memory>
#include <SDL_keycode.h>

#include "CommandClasses.h"
#include "Minigin.h"

#include "FPS.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Text.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "HealthDisplay.h"
#include "Orbit.h"
#include "Texture2D.h"
#include "TrashTheCache.h"
#include "InputManager.h"
#include "Level.h"
#include "LivesDisplay.h"
#include "MenuUI.h"
#include "ScoreComponent.h"
#include "ScoreDisplay.h"
#include "SDL_Audio.h"
#include "ServiceLocator.h"

using namespace Monke;

void initiliaze(const Minigin&)
{
	const auto scene = SceneManager::Get().AddCreateScene("Level1");

	//erviceLocator::RegisterAudioSystem(std::make_unique<dae::AudioSystemLogger>(std::move(std::make_unique<dae::AudioSystemSDL2>())));

	//ServiceLocator::RegisterAudioSystem<Monke::SDL_Audio>();

	const auto pFont{ ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 36) };
	const auto pFontFPS{ ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 15) };
	const auto pFontFScore{ ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 24) };
	//const auto pTextureBackground{ ResourceManager::Get().LoadTexture("Images/background.png") };
	const auto pTextureLogo{ ResourceManager::Get().LoadTexture("Images/logo.tga") };
	const auto pTextureImage1{ ResourceManager::Get().LoadTexture("Images/Fries.png") };
	const auto pTextureImage2{ ResourceManager::Get().LoadTexture("Images/WaterMelon.png") };
	
	//const glm::vec3 posImage1
	//{
	//	middleScreenPos.x - (pTextureImage1->GetSize().x / 2),
	//	middleScreenPos.y - (pTextureImage1->GetSize().y / 2) + 100,
	//	0
	//};
	
	/////player
	//
	////player1
	//const auto pPlayer1{ scene.MakeGameObject() };
	//pPlayer1->AddComponent<Texture>(pTextureImage1);
	//pPlayer1->GetTransform()->SetPosition(middleScreenPos.x - 100, middleScreenPos.y);
	////
	//const auto pScoreCompP1 = pPlayer1->AddComponent<ScoreComponent>();
	//const auto pHealthCompP1 = pPlayer1->AddComponent<HealthComponent>(100.f, 3);
	//
	////player2
	//const auto pPlayer2{ scene.MakeGameObject() };
	//pPlayer2->AddComponent<Texture>(pTextureImage2);
	//pPlayer2->GetTransform()->SetPosition(middleScreenPos.x + 100, middleScreenPos.y);
	//
	//const auto pScoreCompP2 = pPlayer2->AddComponent<ScoreComponent>();
	//const auto pHealthCompP2 = pPlayer1->AddComponent<HealthComponent>(100.f, 3);
	//
	//InputManager::Get().AddCommand<MoveCommand>(SDLK_w, SDLK_d, SDLK_s, SDLK_a, std::make_unique<MoveCommand>(pPlayer1, 100.f));
	//
	//InputManager::Get().AddCommand<MoveCommand>(0, Gamepad::GamepadButton::DPad_Up, Gamepad::GamepadButton::Dpad_Right, Gamepad::GamepadButton::DPad_Down, Gamepad::GamepadButton::DPad_Left, std::make_unique<MoveCommand>(pPlayer2, 200.f));
	//
	////scores
	//
	////score1
	//const auto pScore1{ scene.MakeGameObject() };
	//pScore1->AddComponent<ScoreDisplay>(pScoreCompP1, pHealthCompP1);
	//
	//pScore1->GetTransform()->SetPosition(10, 400);
	//
	////score 2
	//const auto pScore2{ scene.MakeGameObject() };
	//
	//pScore2->AddComponent<ScoreDisplay>(pScoreCompP2, pHealthCompP2);
	//
	//pScore2->GetTransform()->SetPosition(10, 450);
	//
	////lives
	//const auto pLive1{ scene.MakeGameObject() };
	//const auto pLiveDipslayP1 = pLive1->AddComponent<LivesDisplay>(pHealthCompP1);
	//pLive1->GetTransform()->SetPosition(10, 250);
	//
	//pLiveDipslayP1->SetHealthComponent(pHealthCompP1);
	//
	//const auto pLive2{ scene.MakeGameObject() };
	//
	//pLive2->AddComponent<LivesDisplay>(pHealthCompP2);
	//
	//pLive2->GetTransform()->SetPosition(10, 300);
	//
	////commands 
	////InputManager::Get().AddCommand<ScoreCommand>(SDLK_SPACE, InputManager::InputType::OnRelease, std::make_unique<ScoreCommand>(pScoreCompP1, 100.f));
	////InputManager::Get().AddCommand<ScoreCommand>(0, Gamepad::GamepadButton::Button_South, InputManager::InputType::OnRelease, std::make_unique<ScoreCommand>(pScoreCompP2, 100.f));
	//
	//InputManager::Get().AddCommand<DamageCommand>(SDLK_LSHIFT, InputManager::InputType::OnRelease, std::make_unique<DamageCommand>(pHealthCompP1, 50.f));
	//InputManager::Get().AddCommand<DamageCommand>(0, Gamepad::GamepadButton::Button_East, InputManager::InputType::OnRelease, std::make_unique<DamageCommand>(pHealthCompP2, 50.f));
	//
	////control info
	//const auto pExtraInfo{ scene.MakeGameObject() };
	//
	//std::stringstream ss;
	//
	//ss << "Score(space, Button South) Damage(Lshift, button east)|sound plays on live lost";
	//
	//pExtraInfo->AddComponent<Text>(pFontFScore, ss.str(), SDL_Color(255, 0, 0, 255));
	//pExtraInfo->GetTransform()->SetPosition(0, 50);

	const auto pMenu{ scene->MakeGameObject() };

	pMenu->AddComponent<MenuUI>();
}

int main(int, char* [])
{
	//todo check all files for rule of 5

	//original size {640, 480}
	std::unique_ptr<Minigin> engine = std::make_unique<Minigin>("../Data/", 768, 800, 144);

	engine->Run([&engine]() { initiliaze(*engine); });

	return 0;
}