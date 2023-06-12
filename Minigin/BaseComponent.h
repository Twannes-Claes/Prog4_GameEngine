#pragma once

//#include "GameObject.h"

#include <memory>
#include <string>
#include "Errors.h"

namespace Monke
{

	class GameObject;

	class BaseComponent
	{

	public:


		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		//virtual void Initialize() = 0;

		virtual void Update() {}

		virtual void Render() const {}

		virtual void OnGUI() {}

		void Destroy() { m_IsMarkedDead = true; std::cout << "marked\n"; }

		bool IsMarkedDead() const { return m_IsMarkedDead; }

	protected:

		//setted gameobject as a friend so in the addcomponet gameobject can call the constructor (set parent)
		friend class GameObject;
		explicit BaseComponent( GameObject* parent);

		GameObject* GetOwner() const { return m_pParent; }

	private:

		
		GameObject* m_pParent{};

		bool m_IsMarkedDead{ false };

	};

}
