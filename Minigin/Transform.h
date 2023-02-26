#pragma once
#include "DataComponent.h"
#include <glm/glm.hpp>

namespace Monke
{
	class Transform final : public DataComponent
	{
	public:

		Transform() = default;
		virtual ~Transform() override = default;


		void SetPosition(const glm::vec3& pos) { m_Position = pos; }
		void SetPosition(const float x, const float y, const float z = 0) { m_Position = { x,y,z }; }

		glm::vec3 GetPosition() const { return m_Position; }


		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

	private:

		glm::vec3 m_Position{};

	};
}