#pragma once
#include <vector>

#include "BaseComponent.h"

namespace Monke
{
	class Tile;

	class Level final : public Monke::BaseComponent
	{
	public:
		explicit Level(GameObject* parent);

		virtual ~Level() override = default;
		Level(const Level& other) = delete;
		Level(Level&& other) = delete;
		Level& operator=(const Level& other) = delete;
		Level& operator=(Level&& other) = delete;

		void SetFileName(const std::string& fileName) { jsonFileName = fileName; }

		void Initialize() override;

	protected:

	private:

		std::string jsonFileName{};

	};
}

