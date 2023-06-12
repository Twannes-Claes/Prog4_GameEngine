#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace Monke
{
	class Transform;

	class Rigidbody final : public BaseComponent
	{
	public:

		explicit Rigidbody(GameObject* parent, const glm::ivec2 boundaries, const glm::ivec2 sizePlayer, int playerIndex, int gamemode, bool useSecondController = false);

		virtual ~Rigidbody() override = default;
		Rigidbody(const Rigidbody& other) = delete;
		Rigidbody(Rigidbody&& other) = delete;
		Rigidbody& operator=(const Rigidbody& other) = delete;
		Rigidbody& operator=(Rigidbody&& other) = delete;

		virtual void Update() override;

		bool CanJump() const { return m_Velocity.y == 0; }

		void AddVelocityY(const float y) { m_Velocity.y += y; }

	private:

		Transform* m_pTransform{};

		glm::vec2 m_Velocity{0, 0};

		const glm::ivec2 m_Boundaries{};

		const glm::ivec2 m_SizePlayer{};

		const glm::ivec2 m_SizeLevel{ 768 , 800 };

	};
}



