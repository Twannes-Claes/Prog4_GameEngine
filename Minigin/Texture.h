#pragma once
#include "BaseComponent.h"

namespace Monke
{
	class Transform;
	class Texture2D;

	class Texture final : public BaseComponent
	{

	public:

		explicit Texture(GameObject* parent, const std::shared_ptr<Texture2D>& pTexture);
		virtual ~Texture() override = default;

		virtual void Render() const override;

		void SetTexture(const std::shared_ptr<Texture2D>& pTexture) { m_pTexture = pTexture; }

		Texture(const Texture& other) = delete;
		Texture(Texture&& other) = delete;
		Texture& operator=(const Texture& other) = delete;
		Texture& operator=(Texture&& other) = delete;

	private:

		//pointer of the transform to draw the text on the right position
		Transform* m_pTransform{};
		
		//texture pointers
		std::shared_ptr<Texture2D> m_pTexture{};

	};
}



