#pragma once
#include <glm/vec2.hpp>

#include "BaseComponent.h"

namespace Monke
{
	class Transform;
	class Texture;

	class Tile final : public BaseComponent
	{
	public:

		explicit Tile(GameObject* parent);

		virtual ~Tile() override = default;
		Tile(const Tile& other) = delete;
		Tile(Tile&& other) = delete;
		Tile& operator=(const Tile& other) = delete;
		Tile& operator=(Tile&& other) = delete;

		void Initialize() override;

		void SetTile(const bool isBigTile, const glm::vec2& position) { m_IsBigTile = isBigTile; m_Position = position; }

	protected:

	private:

		bool m_IsBigTile{};
		glm::ivec2 m_Position{};

		Texture* m_pTexture{};
	};
}



