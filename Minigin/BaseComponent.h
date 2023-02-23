#pragma once

#include <memory>

namespace Monke
{

	class GameObject;

	class BaseComponent
	{

	public:

		virtual void Update() = 0;

		virtual void Render() const {}

		//	todo: make new updates

		//virtual void LateUpdate() = 0;
		//virtual void FixedUpdate() = 0;

		explicit BaseComponent(std::shared_ptr<GameObject>& pParent);

		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

	protected:

	private:

		std::weak_ptr<GameObject> m_pParent{};

	};
}