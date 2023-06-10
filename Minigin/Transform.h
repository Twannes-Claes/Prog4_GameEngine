#pragma once
#include <glm/glm.hpp>
#include "BaseComponent.h"

namespace Monke
{
	class Transform final : public BaseComponent
	{
	public:

		explicit Transform(GameObject* parent);
		virtual ~Transform() override = default;


		const glm::vec2& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec2& GetWorldPosition();

		void SetPosition(const glm::vec2& pos) { m_LocalPosition = pos; SetTransformDirty(); }
		void SetPosition(const float x, const float y) { m_LocalPosition = { x,y }; SetTransformDirty(); }

		//todo make a function to add to localposition

		void SetLocalPosition(const glm::vec2& pos) { m_LocalPosition = pos; SetTransformDirty(); }
		void SetLocalPosition(const float x, const float y) { m_LocalPosition = { x,y }; SetTransformDirty(); }

		void SetTransformDirty();

		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

	private:

		void UpdateWorldPosition();

		glm::vec2 m_WorldPosition{};
		glm::vec2 m_LocalPosition{};

		//Dirty flag
		bool m_IsDirty{ true };

	};
}
