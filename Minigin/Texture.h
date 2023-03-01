#pragma once
#include "RenderComponent.h"

namespace Monke
{
	class Transform;
	class Texture2D;

	class Texture final : public RenderComponent
	{

	public:

		Texture() = default;

		virtual ~Texture() override = default;

		void Render() const override;

		void SetTexture(const std::shared_ptr<Texture2D>& pTexture);

		Texture(const Texture& other) = delete;
		Texture(Texture&& other) = delete;
		Texture& operator=(const Texture& other) = delete;
		Texture& operator=(Texture&& other) = delete;

	private:

		//weak pointer of the transform to draw the text on the right position
		std::weak_ptr<Transform> mutable m_pTransform{};
		
		//texture pointers
		std::shared_ptr<Texture2D> m_pTexture{};

	};
}



