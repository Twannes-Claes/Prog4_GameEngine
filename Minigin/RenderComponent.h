#pragma once
#include <glm/vec3.hpp>

#include "BaseComponent.h"

namespace Monke
{
	class Texture2D;
	class Transform;

	class RenderComponent : public BaseComponent
	{

	public:

		explicit RenderComponent(std::weak_ptr<GameObject> parent);
		virtual ~RenderComponent() override = default;

		virtual void Initialize() override = 0;
		virtual void Render() const = 0;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

	protected:

		virtual void RenderTexture(const std::weak_ptr<Transform>& pTransform, const std::shared_ptr<Texture2D>& pTexture) const;

		const glm::vec3 m_DefaultDrawPos{};

	};
}



