#pragma once
#include "BaseComponent.h"

namespace Monke
{
	class Player final : public BaseComponent
	{
	public:

		struct PlayerControlInfo
		{
			PlayerControlInfo(int index, int currentGamemode, bool useSecondController)
			{
				playerIndex = index;
				gamemode = currentGamemode;
				secondController = useSecondController;
			}

			int playerIndex{};
			int gamemode{};
			bool secondController{};
		};

		Player(GameObject* pParent, const PlayerControlInfo& infoControls);

		virtual ~Player() override = default;
		Player(const Player& other) = delete;
		Player(Player&& other) = delete;
		Player& operator=(const Player& other) = delete;
		Player& operator=(Player&& other) = delete;

	private:

	};
}



