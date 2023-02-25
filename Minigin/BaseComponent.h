#pragma once

#include <memory>

namespace Monke
{

	class GameObject;

	class BaseComponent
	{

	public:

		BaseComponent() = default;

		virtual ~BaseComponent() = default;


		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		//todo: make a get component function so you dont have to type lock all the time

		void SetParent( const std::weak_ptr<GameObject>& pParent ) { m_pParent = pParent; }

		//template <class T>
		//std::shared_ptr<T> GetComponent() const
		//{
		//	static_assert(std::is_base_of_v<BaseComponent, T>(), "The given class must be inherited from BaseComponent");
		//
		//	if (m_pParent.expired()) { return nullptr; }
		//
		//	return m_pParent.lock()->GetComponent<T>();
		//}

	protected:

		std::weak_ptr<GameObject> m_pParent{};

	private:

	};

	

}