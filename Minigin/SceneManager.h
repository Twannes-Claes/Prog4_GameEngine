#pragma once
#include <vector>
#include <string>
#include <memory>
#include "Singleton.h"

namespace Monke
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene* AddCreateScene(const std::string& name);

		void Update() const;
		void Render() const;
		void OnGUI();

		Scene* GetCurrentScene() const { return m_CurrentScene.get(); }

	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;

		std::shared_ptr<Scene> m_CurrentScene;

		//std::unique_ptr<Scene> m_CurrentScene{};
	};
}
