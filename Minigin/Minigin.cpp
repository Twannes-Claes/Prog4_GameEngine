#include <stdexcept>
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Minigin.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include  "Time.h"

SDL_Window* g_window{};

void PrintSDLVersion()
{
	SDL_version version{};
	SDL_VERSION(&version)
	printf("We compiled against SDL version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	SDL_GetVersion(&version);
	printf("We are linking against SDL version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_IMAGE_VERSION(&version)
	printf("We compiled against SDL_image version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *IMG_Linked_Version();
	printf("We are linking against SDL_image version %u.%u.%u.\n",
		version.major, version.minor, version.patch);

	SDL_TTF_VERSION(&version)
	printf("We compiled against SDL_ttf version %u.%u.%u ...\n",
		version.major, version.minor, version.patch);

	version = *TTF_Linked_Version();
	printf("We are linking against SDL_ttf version %u.%u.%u.\n",
		version.major, version.minor, version.patch);
}

Monke::Minigin::Minigin(const std::string &dataPath, const int width, const int heigth, const int desiredFPS)
:
m_WindowW{ static_cast<float>(width)},
m_WindowH{ static_cast<float>(heigth)},
m_DesiredFPS(desiredFPS)
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	g_window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		heigth,
		SDL_WINDOW_OPENGL
	);
	if (g_window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(g_window);

	ResourceManager::GetInstance().Init(dataPath);

}

Monke::Minigin::~Minigin()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	SDL_Quit();
}

void Monke::Minigin::Run(const std::function<void()>& initiliaze) const
{
	initiliaze();

	const auto& renderer = Renderer::GetInstance();
	const auto& sceneManager = SceneManager::GetInstance();
	const auto& input = InputManager::GetInstance();
	auto& timer = Time::GetInstance();

	//(1000.f / static_cast<float>(m_DesiredFPS))

	const std::chrono::milliseconds fpsTime{ 1000 / m_DesiredFPS };

	bool canContinueLoop = true;



	while (canContinueLoop)
	{
		timer.Update();
		canContinueLoop = input.ProcessInput();
		sceneManager.Update();
		renderer.Render();

		//maybe add a sleep for desired fps
		const auto sleeptime =   timer.GetLastTime() + fpsTime - std::chrono::high_resolution_clock::now();
		std::this_thread::sleep_for(sleeptime);
	}
}
