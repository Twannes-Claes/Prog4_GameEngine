#pragma once
#include <vector>

#include "BaseComponent.h"

namespace Monke
{
	class Tile;

	class Level final : public Monke::BaseComponent
	{
	public:

		explicit Level(GameObject* parent, int levelID, int gamemode, bool useTwoControllers = false);

		virtual ~Level() override = default;
		Level(const Level& other) = delete;
		Level(Level&& other) = delete;
		Level& operator=(const Level& other) = delete;
		Level& operator=(Level&& other) = delete;

	protected:

	private:

	};
}

