#pragma once
#include <memory>
#include <vector>
#include "Transform.h"

namespace Monke
{
	class Texture2D;
	class BaseComponent;
	class UpdateComponent;
	class RenderComponent;

	// todo: this should become final.
	class GameObject
	{
	public:
		virtual void Update();
		virtual void Render() const;

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		template <class T>
		std::shared_ptr<T> GetComponent() const;

		template <class T>
		std::shared_ptr<T> AddComponent();

		template <class T>
		bool HasComponent() const;

		template <class T>
		bool RemoveComponent();

	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};

		//component vectors
		std::vector<std::shared_ptr<UpdateComponent>> m_pUpdateComponents{};
		std::vector<std::shared_ptr<RenderComponent>> m_pRenderComponents{};
	};

	template <class T>
	std::shared_ptr<T> GameObject::GetComponent() const
	{
		//make shared of class
		std::shared_ptr<T> derivedComponent{ nullptr };

		//loop over all updatable components and check if it has the given one
		for (const std::shared_ptr<UpdateComponent>& pComponent : m_pUpdateComponents)
		{
			//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
			if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return derivedComponent;
		}
		//loop over all render components and check if it has the given one
		for (const std::shared_ptr<RenderComponent>& pComponent : m_pRenderComponents)
		{
			if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return derivedComponent;
		}

		return derivedComponent;
	}

	template<class T>
	std::shared_ptr<T> GameObject::AddComponent()
	{
		//check if given class has been inherited form basecomponent
		//https://stackoverflow.com/questions/5084209/check-if-template-argument-is-inherited-from-class && resharper instructing for std::is_base_v

		static_assert(std::is_base_of_v<BaseComponent, T>, "The given class must be inherited from BaseComponent");

		//make the component
		auto pComponent{ std::make_shared<T>(this) };

		//check if component is an updatable or render component, if so add them to the vector
		if(std::is_base_of_v<UpdateComponent, T>)
		{
			//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
			auto pUpdateComponent = std::dynamic_pointer_cast<UpdateComponent>(pComponent);

			m_pUpdateComponents.push_back(pUpdateComponent);
		}
		else if(std::is_base_of_v<RenderComponent, T>)
		{
			auto pRenderComponent = std::dynamic_pointer_cast<RenderComponent>(pComponent);

			m_pUpdateComponents.push_back(pRenderComponent);
		}

		//return the component
		return pComponent;
	}

	template <class T>
	bool GameObject::HasComponent() const
	{
		std::shared_ptr<T> derivedComponent{ nullptr };

		//loop over all updatable components and check if it has the given one
		for (const std::shared_ptr<UpdateComponent>& pComponent : m_pUpdateComponents)
		{
			//https://yunmingzhang.wordpress.com/2020/07/14/casting-shared-pointers-in-c/
			if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return true;
		}
		//loop over all render components and check if it has the given one
		for (const std::shared_ptr<RenderComponent>& pComponent : m_pRenderComponents)
		{
			if ((derivedComponent = std::dynamic_pointer_cast<T>(pComponent))) return true;
		}

		return false;
	}

	template <class T>
	bool GameObject::RemoveComponent()
	{
		//check if given class has been inherited form basecomponent
		//https://stackoverflow.com/questions/5084209/check-if-template-argument-is-inherited-from-class && resharper instructing for std::is_base_v
		
		static_assert(std::is_base_of_v<BaseComponent, T>, "The given class must be inherited from BaseComponent");

		//save bool to check if component has been deleted
		bool removed = false;

		if constexpr (std::is_base_of_v<UpdateComponent, T>)
		{
			auto it = std::remove_if(m_pUpdateComponents.begin(), m_pUpdateComponents.end(),
			[](const std::shared_ptr<BaseComponent> component)
			{
				return std::dynamic_pointer_cast<T>(component) != nullptr;
			});
			if (it != m_pUpdateComponents.end())
			{
				m_pUpdateComponents.erase(it);
				removed = true;
			}
		}
		else if constexpr (std::is_base_of_v<RenderComponent, T>)
		{
			auto it = std::remove_if(m_pRenderComponents.begin(), m_pRenderComponents.end(),
			[](const std::shared_ptr<BaseComponent> component)
			{
				return std::dynamic_pointer_cast<T>(component) != nullptr;
			});
			if (it != m_pRenderComponents.end())
			{
				m_pRenderComponents.erase(it);
				removed = true;
			}
		}
		return removed;
	}
}
