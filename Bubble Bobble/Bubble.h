#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace Monke
{
	class AnimationTexture;
	class Transform;

	class Bubble final : public BaseComponent
	{
	public:

		explicit Bubble(GameObject* pParent, const glm::vec2 position);

		virtual ~Bubble() override = default;
		Bubble(const Bubble& other) = delete;
		Bubble(Bubble&& other) = delete;
		Bubble& operator=(const Bubble& other) = delete;
		Bubble& operator=(Bubble&& other) = delete;

		virtual void Update() override;

	private:

		Transform* m_pTransform;

		AnimationTexture* m_pTexture;

		const float m_MaxLifeTime{ 3.f };

		float m_CurrentLifeTime{};
	};
}



