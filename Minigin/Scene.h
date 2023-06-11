#pragma once
#include "SceneManager.h"
#include "GameObject.h"

namespace Monke
{

	class Scene final
	{
		//friend Scene* SceneManager::CreateScene(const std::string& name);

	public:
		explicit Scene(std::string name);

		GameObject* MakeGameObject();

		void Add(std::unique_ptr<GameObject> object);
		void Remove(const std::unique_ptr<GameObject> object);
		void RemoveAll();

		void Update();
		void Render() const;
		void OnGUI();

		~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private: 

		std::string m_name;
		std::vector < std::unique_ptr<GameObject> > m_objects{};

		static unsigned int m_idCounter; 
	};

}
