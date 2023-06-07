#pragma once
#include <memory>
#include <vector>
#include <string>

#include "BaseComponent.h"

namespace Monke
{
	class Transform;
	class Texture2D;

	class GameObject final
	{

	public:

		//scene manager functions
		void Initialize() const;
		void Update();
		void Render() const;
		void OnGUI();

		//scenegraph functions
		void SetParent(GameObject* newParent, const bool keepWorldPosition = false);
		GameObject* GetParent() const { return m_pParent; }

		const std::vector<GameObject*>& GetAllChildren() const { return m_pChildren; }

		Transform* GetTransform() const { return m_pTransform; }

		void Destroy();
		bool IsMarkedDead() const { return m_IsMarkedDead; }

		void SetActive(const bool isActive) { m_IsActive = isActive; }

		bool IsActive() const { return m_IsActive; }

		//THE BIG SIX
		GameObject();

		~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

#pragma region Template_Component_Classes

		template <class T>
		T* GetComponent() const;

		template <class T>
		T* AddComponent();

		template <class T>
		bool HasComponent() const;

		template <class T>
		bool RemoveComponent();

#pragma endregion

	private:

#pragma region Template_ComponentCheck_Functions
		//private functions to make less code
		//template<typename T, typename V>
		//bool GetComponentCheck(std::shared_ptr<T> derivedComponent, std::vector<std::shared_ptr<V>>& vector)
		//{
		//	for (const std::shared_ptr<V>& pComponent : vector)
		//	{
		//		//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
		//		if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return true;
		//	}
		//
		//	return false;
		//}
		//
		//template<typename T, typename V>
		//bool AddComponentCheck(std::shared_ptr<T> derivedComponent, std::vector<std::shared_ptr<V>>& vector)
		//{
		//	if constexpr (std::is_base_of_v<V, T>)
		//	{
		//		//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
		//		auto pVComponent = std::dynamic_pointer_cast<V>(derivedComponent);
		//
		//		vector.push_back(pVComponent);
		//		return true;
		//	}
		//
		//	return false;
		//}
		//
		//template<typename T, typename V>
		//bool HasComponentCheck(std::shared_ptr<T> derivedComponent, std::vector<std::shared_ptr<V>>& vector)
		//{
		//	for (const std::shared_ptr<V>& component : vector)
		//	{
		//		//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
		//		if ((derivedComponent = std::dynamic_pointer_cast<T>(component))) return true;
		//	}
		//
		//	return false;
		//}
		//
		//template<typename T, typename V>
		//bool RemoveComponentCheck(std::vector<std::shared_ptr<V>>& vector)
		//{
		//	if constexpr (std::is_base_of_v<V, T>)
		//	{
		//		//find the first component that matches the component in the vector
		//		auto it = std::remove_if(vector.begin(), vector.end(), []
		//		(const std::shared_ptr<BaseComponent>& component)
		//			{
		//				//check if the component can be casted to the template type
		//				return std::dynamic_pointer_cast<T>(component) != nullptr;
		//			});
		//		//if i components has been found erase it and turn the remove flag to true
		//		if (it != vector.end())
		//		{
		//			vector.erase(it);
		//			return true;
		//		}
		//	}
		//
		//	return false;
		//}
#pragma endregion

		template <class T>
		void CleanUpVector(std::vector<std::unique_ptr<T>>& v)
		{
			static_assert(std::is_base_of_v<BaseComponent, T>, "The given class must be inherited from BaseComponent");

			//auto it = std::remove_if(v.begin(), v.end(),
			//[]
			//(const std::shared_ptr<BaseComponent>& component)
			//{
			//	//check if the component can be casted to the template type
			//	return component->IsMarkedDead();
			//});
			////if i components has been found erase it and turn the remove flag to true
			//if (it != v.end())
			//{
			//	v.erase(it);
			//}

			//remove all elements from the vector if is marked as dead

			v.erase(std::remove_if(begin(v), end(v), [](const auto& pComponent)
			{
				return pComponent->IsMarkedDead();
			}), end(v));
		}

		Transform* m_pTransform{};

		GameObject* m_pParent{};

		std::vector< GameObject* > m_pChildren{};

		std::vector<std::unique_ptr< BaseComponent >> m_pComponents{};

		bool m_IsMarkedDead{ false };

		bool m_IsActive{ true };
	};

#pragma region Template_Component_Logic

	template <class T>
	T* GameObject::GetComponent() const
	{
		static_assert(std::is_base_of_v<BaseComponent, T>, "The given class must be inherited from BaseComponent");

		//make pointer
		T* derivedComponent{ nullptr };

		//go trough all and return if it has found one
		for (const auto& pComponent : m_pComponents)
		{
			if(derivedComponent = dynamic_cast<T*>(pComponent.get()); derivedComponent != nullptr)
			{
				return derivedComponent;
			}
		}

		return nullptr;
	}

	template<class T>
	T* GameObject::AddComponent()
	{
		//check if given class has been inherited form basecomponent
		//https://stackoverflow.com/questions/5084209/check-if-template-argument-is-inherited-from-class && resharper instructing for std::is_base_v

		static_assert(std::is_base_of_v<BaseComponent, T> , "The given class must be inherited from BaseComponent");

		//compiler gives error when this is not constexpr because cant convert Transform to T*
		if constexpr (std::is_same<Transform, T>())
		{
			if (GetComponent<Transform>())
			{
				//todo make a warning logger
				return m_pTransform;
			}
		}

		//make the component

		auto pComponent{ std::make_unique<T>( this ) };

		auto newComponent =  pComponent.get();

		m_pComponents.push_back(std::move(pComponent));

		//return pointer of the component
		return newComponent;
	}

	template <class T>
	bool GameObject::HasComponent() const
	{
		static_assert(std::is_base_of_v<BaseComponent, T>, "The given class must be inherited from BaseComponent");

		//make pointer
		T* derivedComponent{ nullptr };

		//go trough all and return if it has found one
		for (const auto& pComponent : m_pComponents)
		{
			if (derivedComponent = dynamic_cast<T*>(pComponent.get()); derivedComponent != nullptr)
			{
				return true;
			}
		}

		return false;
	}

	template <class T>
	bool GameObject::RemoveComponent()
	{
		//check if given class has been inherited form basecomponent
		//https://stackoverflow.com/questions/5084209/check-if-template-argument-is-inherited-from-class && resharper instructing for std::is_base_v
		
		static_assert(std::is_base_of_v<BaseComponent, T>, "The given class must be inherited from BaseComponent");
		static_assert(std::is_same<Transform, T>(), "Cannon remove a transform");

		////find the first component that matches the component in the vector
		//auto it = std::remove_if(m_pComponents.begin(), m_pComponents.end(),[]
		//(const std::shared_ptr<BaseComponent>& component)
		//{
		//	//check if the component can be casted to the template type
		//	return std::dynamic_pointer_cast<T>(component) != nullptr;
		//});
		////if i components has been found erase it and turn the remove flag to true
		//if (it != m_pComponents.end())
		//{
		//	(*it)->Destroy();
		//	return true;
		//}

		//try to get the component if so destroy
		if (T * pRemoveComp{ GetComponent<T>() })
		{
			Destroy(pRemoveComp);

			return true;
		}

		//return if the component has been removed
		return false;
	}

#pragma endregion

}
