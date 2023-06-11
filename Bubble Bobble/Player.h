#pragma once
#include "BaseComponent.h"

namespace Monke
{
	class Player final : public BaseComponent
	{
	public:

		Player(GameObject* pParent, int):BaseComponent(pParent){}

		virtual ~Player() override = default;
		Player(const Player& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) = delete;

	private:
	};
}



