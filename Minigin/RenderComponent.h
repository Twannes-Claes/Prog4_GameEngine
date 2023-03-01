#pragma once
#include <glm/vec3.hpp>

#include "BaseComponent.h"

namespace Monke
{
	class RenderComponent : public BaseComponent
	{

	public:

		RenderComponent() = default;

		virtual void Render() const = 0;

		virtual ~RenderComponent() override = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

	protected:

		glm::vec3 m_DefaultDrawPos{};

	};
}



