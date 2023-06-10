#include "SceneManager.h"
#include "Scene.h"

void Monke::SceneManager::Update() const
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void Monke::SceneManager::Render() const
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void Monke::SceneManager::OnGUI()
{
	for (const auto& scene : m_scenes)
	{
		scene->OnGUI();
	}
}

Monke::Scene& Monke::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}


