#include "Scene.h"

using namespace Monke;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(std::string name) : m_name(std::move(name)) {}

Scene::~Scene() = default;

GameObject* Scene::MakeGameObject()
{
	std::unique_ptr pGameObject{ std::make_unique<GameObject>(this) };

	GameObject* newObject = pGameObject.get();

	Add(std::move(pGameObject));

	return newObject;
}

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const std::unique_ptr<GameObject> object)
{
	std::erase(m_objects, object);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Initialize() const
{
	for (auto& object : m_objects)
	{
		object->Initialize();
	}
}

void Scene::Update()
{
	for (const auto& object : m_objects)
	{
		object->Update();
	}

	std::erase_if(m_objects, 
	[](const auto& obj) {
	return obj->IsMarkedDead();
	});

}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::OnGUI()
{
	for (const auto& object : m_objects)
	{
		object->OnGUI();
	}
}

