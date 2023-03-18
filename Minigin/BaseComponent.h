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

		virtual void Initialize() = 0;

		virtual void OnGUI() {}

		//todo: make a get component function so you dont have to type lock all the time
#pragma region TryGetComponent
		
#pragma endregion
		void Destroy() { m_IsMarkedDead = true; }

		bool IsMarkedDead() const { return m_IsMarkedDead; }

	protected:

		//setted gameobject as a friend so in the addcomponet gameobject can call SetParent
		friend class GameObject;
		explicit BaseComponent( std::weak_ptr<GameObject> parent);
		std::weak_ptr<GameObject> GetOwner() const { return m_pParent; }
		//template <class T>
		//void CacheComponent(std::weak_ptr<T>& pComponent, const std::string& text)
		//{
		//	static_assert(std::is_base_of_v<BaseComponent, T>(), "The given class must be inherited from BaseComponent");
		//
		//	pComponent = GetParent().lock()->GetComponent<T>();
		//
		//	if (pComponent.expired())
		//	{
		//		const auto error = Expired_Weak_Ptr(__FILE__, __LINE__, text);
		//	}
		//}
		//
		//template <class T>
		//std::shared_ptr<T> GetComponent() const
		//{
		//	static_assert(std::is_base_of_v<BaseComponent, T>(), "The given class must be inherited from BaseComponent");
		//
		//	if (m_pParent.expired()) { return nullptr; }
		//
		//	return m_pParent.lock()->GetComponent<T>();
		//}

	private:

		
		std::weak_ptr<GameObject> m_pParent{};

		bool m_IsMarkedDead{ false };

	};

}
