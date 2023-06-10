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

		explicit Tile(GameObject* parent, const bool isBigTile, const glm::ivec2 position, int levelID);

		virtual ~Tile() override = default;
		Tile(const Tile& other) = delete;
		Tile(Tile&& other) = delete;
		Tile& operator=(const Tile& other) = delete;
		Tile& operator=(Tile&& other) = delete;

	protected:

	private:

		Texture* m_pTexture{};
	};
}



