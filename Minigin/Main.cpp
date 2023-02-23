#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"

namespace Monke
{
	void load()
	{
		auto& scene = SceneManager::GetInstance().CreateScene("Demo");
		
		auto go = std::make_shared<GameObject>();
		go->SetTexture("background.tga");
		scene.Add(go);
		
		go = std::make_shared<GameObject>();
		go->SetTexture("logo.tga");
		go->SetPosition(216, 180);
		scene.Add(go);
		
		auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
		const auto to = std::make_shared<TextObject>("Programming 4 Assignment", font);
		to->SetPosition(80, 20);
		scene.Add(to);
	}

	int main(int, char* [])
	{
		const Minigin engine("../Data/");
		engine.Run(load);
		return 0;
	}
}