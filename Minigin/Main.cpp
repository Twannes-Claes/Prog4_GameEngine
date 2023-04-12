#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include <memory>

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
#include "Orbit.h"
#include "Texture2D.h"
#include "TrashTheCache.h"
#include "InputManager.h"

using namespace Monke;

void initiliaze(const Minigin& engine)
{
	auto& scene = SceneManager::GetInstance().CreateScene("Assignment");
	
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 36) };
	const auto pFontFPS{ ResourceManager::GetInstance().LoadFont("Fonts/Lingua.otf", 15) };
	const auto pTextureBackground{ ResourceManager::GetInstance().LoadTexture("Images/background.tga") };
	const auto pTextureLogo{ ResourceManager::GetInstance().LoadTexture("Images/logo.tga") };
	const auto pTextureImage1 {ResourceManager::GetInstance().LoadTexture("Images/Fries.png") };
	const auto pTextureImage2{ ResourceManager::GetInstance().LoadTexture("Images/WaterMelon.png") };

	//background object
	const auto pBackground{ scene.MakeGameObject() };
	pBackground->AddComponent<Transform>()->SetPosition(1,1);
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
	pLogo->AddComponent<Transform>()->SetPosition(posLogo.x, posLogo.y);

	//header text object
	const auto pText{ scene.MakeGameObject() };
	const auto pTextComp{ pText->AddComponent<Text>() };
	pText->AddComponent<Transform>()->SetPosition(80, 80);
	//
	pTextComp->SetFont(pFont);
	pTextComp->SetText("Programming 4 Assignment");

	//FPS object
	const auto pFPS{ scene.MakeGameObject() };
	pFPS->AddComponent<Transform>()->SetPosition(10, 10);
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

	///orbiting images
	const auto pImage1{ scene.MakeGameObject() };
	pImage1->AddComponent<Texture>()->SetTexture(pTextureImage1);
	pImage1->AddComponent<Transform>()->SetPosition(middleScreenPos.x - 100, middleScreenPos.y);

	//const auto pOrbit = pImage1->AddComponent<Orbit>();
	//pOrbit->SetRadius(25.f);
	//pOrbit->SetRotationSpeed(45.f);
	//pOrbit->SetCenter(posImage1);

	scene.Add(pImage1);

	const auto pImage2{ scene.MakeGameObject() };
	pImage2->AddComponent<Texture>()->SetTexture(pTextureImage2);
	pImage2->AddComponent<Transform>()->SetPosition(middleScreenPos.x + 100, middleScreenPos.y);

	//const auto pOrbit2 = pImage2->AddComponent<Orbit>();
	//pOrbit2->SetRadius(65.f);
	//pOrbit2->SetRotationSpeed(-60.f);

	scene.Add(pImage2);

	//const auto pImage3{ scene.MakeGameObject() };
	//pImage3->AddComponent<Texture>()->SetTexture(pTextureImage2);
	//pImage3->AddComponent<Transform>()->SetPosition(middleScreenPos.x, middleScreenPos.y);
	//
	//scene.Add(pImage3);

	//pImage1->AddChild(pImage2);

	//const auto GUI{ scene.MakeGameObject() };
	//GUI->AddComponent<TrashTheCache>();

	//auto firstPlayer = InputManager::GetInstance().AddCommand<MoveCommand>(0, Gamepad::GamepadButton::Left_Joystick, InputManager::InputType::Axis, pImage1.get());
	//firstPlayer->SetSpeed(100.f);

	//auto secondPlayer = InputManager::GetInstance().AddCommand<MoveCommand>(1, Gamepad::GamepadButton::Left_Joystick, InputManager::InputType::Axis, pImage2.get());
	//secondPlayer->SetSpeed(200.f);

	const auto firstPlayer = InputManager::GetInstance().AddCommand<MoveCommand>(SDLK_w, SDLK_d, SDLK_s, SDLK_a, pImage1.get());
	firstPlayer->SetSpeed(100.f);

	const auto secondPlayer = InputManager::GetInstance().AddCommand<MoveCommand>(0, Gamepad::GamepadButton::DPad_Up, Gamepad::GamepadButton::Dpad_Right, Gamepad::GamepadButton::DPad_Down, Gamepad::GamepadButton::DPad_Left, pImage2.get());
	secondPlayer->SetSpeed(200.f);

	//const auto thirdPlayer = InputManager::GetInstance().AddCommand<MoveCommand>(1, Gamepad::GamepadButton::Left_Joystick, InputManager::InputType::Axis, pImage3.get());
	//thirdPlayer->SetSpeed(150.f);
	
}

int main(int, char* [])
{
	//original size {640, 480}
	std::unique_ptr<Minigin> engine = std::make_unique<Minigin>("../Data/", 640, 480, 144);

	engine->Run([&engine]() { initiliaze(*engine); });

	return 0;
}
