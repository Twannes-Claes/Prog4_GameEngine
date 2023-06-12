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
	const auto scene = SceneManager::Get().AddCreateScene("MainMenu");

	ServiceLocator::RegisterAudioSystem<Monke::SDL_Audio>();

	const auto pMenu{ scene->MakeGameObject() };

	pMenu->AddComponent<MenuUI>();

	std::cout << "\n\nControls:\n\n" << "NUMPAD or ARROWS for gamemode\n\n" << "NUMPAD or WASD to move\n\n" << "Space or Button A to jump\n\n" << "LSHIFT or Button X to shoot\n\n"
	<< "ESCAPE or Button B to return to menu || F1 or Button Y to skip scene\n\n" << "M to (un)mute\n\n";
}

int main(int, char* [])
{
	//todo check all files for rule of 5

	//original size {640, 480}
	std::unique_ptr<Minigin> engine = std::make_unique<Minigin>("../Data/", 768, 800, 144);

	engine->Run([&engine]() { initiliaze(*engine); });

	return 0;
}