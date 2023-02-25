#include <SDL.h>

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "FPS.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "Text.h"
#include "Texture.h"
#include "Transform.h"
#include "GameObject.h"

using namespace Monke;

void initiliaze()
{

	auto& scene = SceneManager::GetInstance().CreateScene("Assignment");
	
	const auto pFont{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 36) };
	const auto pFontFPS{ ResourceManager::GetInstance().LoadFont("Lingua.otf", 15) };
	const auto pTextureBackground{ ResourceManager::GetInstance().LoadTexture("background.tga") };
	const auto pTextureLogo{ ResourceManager::GetInstance().LoadTexture("logo.tga") };

	//background object
	const auto pBackground{ scene.MakeGameObject() };
	pBackground->AddComponent<Texture>()->SetTexture(pTextureBackground);
	pBackground->AddComponent<Transform>()->SetPosition(0,0);

	//logo object
	const auto pLogo{ scene.MakeGameObject() };
	pLogo->AddComponent<Transform>()->SetPosition( 216, 200 );
	pLogo->AddComponent<Texture>()->SetTexture(pTextureLogo);

	//header text object
	const auto pText{ scene.MakeGameObject() };
	pText->AddComponent<Transform>()->SetPosition(80, 80);
	//
	const auto pTextComp{ pText->AddComponent<Text>() };
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

}

int main(int, char* [])
{
	const Minigin engine("../Data/");
	engine.Run(initiliaze);
	return 0;
}
