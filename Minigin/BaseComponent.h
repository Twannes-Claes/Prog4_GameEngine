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

		//todo: MAKE A SET PARENT FUNCTION SO YOU DONT HAVE TO KEEP USING THE INHERITED CONSTRUCTOR FOR THE PARENT
		//todo: make a get component function so you dont have to type lock all the time

		void SetParent( std::weak_ptr<GameObject> pParent ) { m_pParent = pParent; }

	protected:

		std::weak_ptr<GameObject> m_pParent{};

	private:

	};

}