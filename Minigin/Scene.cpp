#include "Scene.h"
#include "GameObject.h"

using namespace Monke;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(std::string name) : m_name(std::move(name)) {}

Scene::~Scene() = default;

std::shared_ptr<GameObject> Scene::MakeGameObject()
{
	std::shared_ptr pGameObject{ std::make_shared<GameObject>() };

	Add(pGameObject);

	return pGameObject;
}

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const std::shared_ptr<GameObject>& object)
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
	[](const std::shared_ptr<GameObject>& obj) {
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

