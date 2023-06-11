#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace Monke
{
	class Rigidbody final : public BaseComponent
	{
	public:

		explicit Rigidbody(GameObject* parent, const glm::ivec2 boundaries);

		virtual ~Rigidbody() override = default;
		Rigidbody(const Rigidbody& other) = delete;
		Rigidbody(Rigidbody&& other) = delete;
		Rigidbody& operator=(const Rigidbody& other) = delete;
		Rigidbody& operator=(Rigidbody&& other) = delete;

	private:


	};
}



