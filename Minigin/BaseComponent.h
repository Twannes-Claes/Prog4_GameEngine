#pragma once

#include <memory>

namespace Monke
{

	class GameObject;

	class BaseComponent
	{

		public:

		explicit BaseComponent(std::weak_ptr<GameObject>& pParent);

		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		// todo: MAKE A SET PARENT FUNCTION SO YOU DONT HAVE TO KEEP USING THE INHERITED CONSTRUCTOR FOR THE PARENT

		protected:

		std::weak_ptr<GameObject> m_pParent{};

	};

}