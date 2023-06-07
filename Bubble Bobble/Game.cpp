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
#include "LivesDisplay.h"
#include "ScoreComponent.h"
#include "ScoreDisplay.h"
#include "SDL_Audio.h"
#include "ServiceLocator.h"

using namespace Monke;

void initiliaze(const Minigin& engine)
{
	auto& scene = SceneManager::Get().CreateScene("Assignment");

	//erviceLocator::RegisterAudioSystem(std::make_unique<dae::AudioSystemLogger>(std::move(std::make_unique<dae::AudioSystemSDL2>())));

	ServiceLocator::RegisterAudioSystem<Monke::SDL_Audio>();

	const auto pFont{ ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 36) };
	const auto pFontFPS{ ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 15) };
	const auto pFontFScore{ ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 24) };
	const auto pTextureBackground{ ResourceManager::Get().LoadTexture("Images/background.tga") };
	const auto pTextureLogo{ ResourceManager::Get().LoadTexture("Images/logo.tga") };
	const auto pTextureImage1{ ResourceManager::Get().LoadTexture("Images/Fries.png") };
	const auto pTextureImage2{ ResourceManager::Get().LoadTexture("Images/WaterMelon.png") };

	//background object
	const auto pBackground{ scene.MakeGameObject() };
	pBackground->GetTransform()->SetPosition(1, 1);
	pBackground->AddComponent<Texture>()->SetTexture(pTextureBackground);

	//logo object
	const auto pLogo{ scene.MakeGameObject() };
	pLogo->AddComponent<Texture>()->SetTexture(pTextureLogo);
	//
	const glm::vec2 middleScreenPos
	{
		(engine.GetWindowW() / 2),
		(engine.GetWindowH() / 2)
	};
	const glm::vec2 posLogo
	{
		middleScreenPos.x - (pTextureLogo->GetSize().x / 2),
		middleScreenPos.y - (pTextureLogo->GetSize().y / 2) - 50
	};
	//
	pLogo->GetTransform()->SetPosition(posLogo.x, posLogo.y);

	//header text object
	const auto pText{ scene.MakeGameObject() };
	const auto pTextComp{ pText->AddComponent<Text>() };
	pText->GetTransform()->SetPosition(80, 80);
	//
	pTextComp->SetFont(pFont);
	pTextComp->SetText("Programming 4 Assignment");

	//FPS object
	const auto pFPS{ scene.MakeGameObject() };
	pFPS->GetTransform()->SetPosition(10, 10);
	pFPS->AddComponent<FPS>();
	//
	const auto pTextFPS{ pFPS->AddComponent<Text>() };
	pTextFPS->SetFont(pFontFPS);
	pTextFPS->SetColor(255, 255, 0, 200);

	const glm::vec3 posImage1
	{
		middleScreenPos.x - (pTextureImage1->GetSize().x / 2),
		middleScreenPos.y - (pTextureImage1->GetSize().y / 2) + 100,
		0
	};

	///player

	//player1
	const auto pPlayer1{ scene.MakeGameObject() };
	pPlayer1->AddComponent<Texture>()->SetTexture(pTextureImage1);
	pPlayer1->GetTransform()->SetPosition(middleScreenPos.x - 100, middleScreenPos.y);

	const auto pScoreCompP1 = pPlayer1->AddComponent<ScoreComponent>();
	const auto pHealthCompP1 = pPlayer1->AddComponent<HealthComponent>();
	pHealthCompP1->SetMaxHealth(100);
	pHealthCompP1->SetAmountLives(3);

	//player2
	const auto pPlayer2{ scene.MakeGameObject() };
	pPlayer2->AddComponent<Texture>()->SetTexture(pTextureImage2);
	pPlayer2->GetTransform()->SetPosition(middleScreenPos.x + 100, middleScreenPos.y);

	const auto pScoreCompP2 = pPlayer2->AddComponent<ScoreComponent>();
	const auto pHealthCompP2 = pPlayer1->AddComponent<HealthComponent>();
	pHealthCompP2->SetMaxHealth(100);
	pHealthCompP2->SetAmountLives(3);

	InputManager::Get().AddCommand<MoveCommand>(SDLK_w, SDLK_d, SDLK_s, SDLK_a, std::make_unique<MoveCommand>(pPlayer1, 100.f));

	InputManager::Get().AddCommand<MoveCommand>(0, Gamepad::GamepadButton::DPad_Up, Gamepad::GamepadButton::Dpad_Right, Gamepad::GamepadButton::DPad_Down, Gamepad::GamepadButton::DPad_Left, std::make_unique<MoveCommand>(pPlayer2, 200.f));

	//scores

	//score1
	const auto pScore1{ scene.MakeGameObject() };
	const auto pDisplay1 = pScore1->AddComponent<ScoreDisplay>();

	pDisplay1->SetScoreComponent(pScoreCompP1);
	pDisplay1->SetHealthComponent(pHealthCompP1);

	pScore1->GetTransform()->SetPosition(10, 400);

	//score 2
	const auto pScore2{ scene.MakeGameObject() };
	const auto pTextScore2 = pScore2->AddComponent<Text>();

	pTextScore2->SetColor(255, 255, 0, 255);
	pTextScore2->SetFont(pFontFScore);

	const auto pDisplay2 = pScore2->AddComponent<ScoreDisplay>();

	pDisplay2->SetHealthComponent(pHealthCompP2);
	pDisplay2->SetScoreComponent(pScoreCompP2);

	pScore2->GetTransform()->SetPosition(10, 450);

	//lives
	const auto pLive1{ scene.MakeGameObject() };
	const auto pLiveDipslayP1 = pLive1->AddComponent<LivesDisplay>();
	pLive1->GetTransform()->SetPosition(10, 250);

	pLiveDipslayP1->SetHealthComponent(pHealthCompP1);

	const auto pLive2{ scene.MakeGameObject() };
	const auto pTextLive2 = pLive2->AddComponent<Text>();

	pTextLive2->SetColor(255, 255, 0, 255);
	pTextLive2->SetFont(pFontFScore);

	const auto pLiveDipslayP2 = pLive2->AddComponent<LivesDisplay>();
	pLiveDipslayP2->SetHealthComponent(pHealthCompP2);

	pLive2->GetTransform()->SetPosition(10, 300);

	//commands 
	//InputManager::Get().AddCommand<ScoreCommand>(SDLK_SPACE, InputManager::InputType::OnRelease, std::make_unique<ScoreCommand>(pScoreCompP1, 100.f));
	//InputManager::Get().AddCommand<ScoreCommand>(0, Gamepad::GamepadButton::Button_South, InputManager::InputType::OnRelease, std::make_unique<ScoreCommand>(pScoreCompP2, 100.f));

	InputManager::Get().AddCommand<DamageCommand>(SDLK_LSHIFT, InputManager::InputType::OnRelease, std::make_unique<DamageCommand>(pHealthCompP1, 50.f));
	InputManager::Get().AddCommand<DamageCommand>(0, Gamepad::GamepadButton::Button_East, InputManager::InputType::OnRelease, std::make_unique<DamageCommand>(pHealthCompP2, 50.f));


	//control info
	const auto pExtraInfo{ scene.MakeGameObject() };

	const auto pExtraTextText = pExtraInfo->AddComponent<Text>();
	pExtraTextText->SetColor(255, 0, 0, 255);
	pExtraTextText->SetFont(pFontFPS);

	std::stringstream ss;

	ss << "Score(space, Button South) Damage(Lshift, button east)|sound plays on live lost";

	pExtraTextText->SetText(ss.str());

	pExtraInfo->GetTransform()->SetPosition(0, 50);
}

int main(int, char* [])
{
	//todo check all files for rule of 5

	//original size {640, 480}
	std::unique_ptr<Minigin> engine = std::make_unique<Minigin>("../Data/", 640, 480, 144);

	engine->Run([&engine]() { initiliaze(*engine); });

	return 0;
}