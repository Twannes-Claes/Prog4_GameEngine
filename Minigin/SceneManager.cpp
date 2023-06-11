#include "SceneManager.h"

#include "InputManager.h"
#include "Scene.h"

void Monke::SceneManager::Update() const
{
	//for(auto& scene : m_scenes)
	//{
	//	scene->Update();
	//}
	if (m_CurrentScene)
	{
		m_CurrentScene->Update();
	}
}

void Monke::SceneManager::Render() const
{
	//for (const auto& scene : m_scenes)
	//{
	//	scene->Render();
	//}
	if (m_CurrentScene)
	{
		m_CurrentScene->Render();
	}
}

void Monke::SceneManager::OnGUI()
{
	//for (const auto& scene : m_scenes)
	//{
	//	scene->OnGUI();
	//}

	if(m_CurrentScene)
	{
		m_CurrentScene->OnGUI();
	}
}

Monke::Scene* Monke::SceneManager::AddCreateScene(const std::string& name)
{
	//const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	InputManager::Get().ClearCommands();

	m_CurrentScene = std::make_shared<Scene>(name);
	return m_CurrentScene.get();
}


