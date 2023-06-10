#pragma once

#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace Monke
{
	class Transform;

	class Orbit final : public BaseComponent
	{

	public:

		explicit Orbit( GameObject* parent);
		virtual ~Orbit() override = default;

		virtual void Update() override;

		void SetRadius(const float radius) { m_Radius = radius; }
		void SetRotationSpeed(const float speed) { m_RotSpeed = speed; }
		void SetCenter(const glm::vec2& center) { m_Center = center; }

		Orbit(const Orbit& other) = delete;
		Orbit(Orbit&& other) = delete;
		Orbit& operator=(const Orbit& other) = delete;
		Orbit& operator=(Orbit&& other) = delete;


		Transform* m_pTransform;

		float m_Rotation{};

		float m_Radius;
		float m_RotSpeed;

		glm::vec2 m_Center{};

	};

}

