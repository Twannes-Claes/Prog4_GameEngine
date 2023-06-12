#include "Level.h"

#include <glm/vec2.hpp>

#include <fstream>

#include "GameObject.h"
#include "InputManager.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "RapidJson/document.h"
#include "RapidJson/istreamwrapper.h"

#include "Tile.h"
#include "Transform.h"

#include "SDL_keycode.h"

#include "CommandClasses.h"
#include "FPS.h"
#include "Gamepad.h"
#include "Player.h"

Monke::Level::Level(GameObject* parent, int levelID, int gamemode, bool useTwoControllers)
:BaseComponent(parent)
{
	//if level ID or gamemode are invalid set them to default
	if (levelID > 3 || levelID < 1) levelID = 1;
	if (gamemode > 3 || gamemode < 1) gamemode = 1;

	//get the filename
	const std::string fileName = ResourceManager::Get().GetPath() + "Levels/Level" + std::to_string(levelID) + "/Level" + std::to_string(levelID) + ".json";

	//opening input file stream
	if (std::ifstream inputStream{ fileName })
	{
		//making variables for json reader
		rapidjson::IStreamWrapper isw{ inputStream };
		rapidjson::Document sceneDoc;
		sceneDoc.ParseStream(isw);

		//check if the json is an array
		if (sceneDoc.IsArray())
		{
			//loop trough all object
			for (auto it = sceneDoc.Begin(); it != sceneDoc.End(); ++it)
			{
				const rapidjson::Value& object{ *it };

				//check if variables are correct
				if (object.HasMember("name") && object.HasMember("positions"))
				{
					//check and get the object name
					const std::string objectName{ object["name"].GetString() };

					bool isBigTile = objectName == "bigTile" ? true : false;

					bool isPlayer = objectName == "players";

					//check if the position variable is an array
					if (const rapidjson::Value& positions{ object["positions"] }; positions.IsArray())
					{
						int playerIndex{0};

						//loop trough all the positions
						for (auto posIt = positions.Begin(); posIt != positions.End(); ++posIt)
						{
							//save the position
							const rapidjson::Value& currentPos{ *posIt };

							//check if the position is an array and holds 2 values
							if (currentPos.IsArray() && currentPos.Size() == 2)
							{
								glm::ivec2 worldPos{};

								worldPos.x = currentPos[0].GetInt();
								worldPos.y = currentPos[1].GetInt();


								if(isPlayer)
								{
									++playerIndex;

									//check to see if it has to spawn one or two players based on gamemode
									if(gamemode > 1 || (gamemode == 1 && playerIndex == 1))
									{
										//create new object in scene
										auto newObj = GetOwner()->AddCreateChild();

										newObj->GetTransform()->SetPosition(worldPos);

										newObj->AddComponent<Player>(Player::PlayerControlInfo(playerIndex, gamemode, useTwoControllers));
									}
								}
								else
								{
									//create new object in scene
									auto newObj = GetOwner()->AddCreateChild();

									newObj->AddComponent<Tile>(isBigTile, worldPos, levelID);
								}
							}
						}
					}
				}
			}
		}

		//contorls for menu control
		InputManager::Get().AddCommand(SDLK_F1, InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(levelID, gamemode));
		InputManager::Get().AddCommand(0, Gamepad::GamepadButton::Button_North, InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(levelID, gamemode));

		InputManager::Get().AddCommand(SDLK_ESCAPE, InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(3, gamemode));
		InputManager::Get().AddCommand(0, Gamepad::GamepadButton::Button_East, InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(3, gamemode));



		if(useTwoControllers)
		{
			InputManager::Get().AddCommand(1, Gamepad::GamepadButton::Button_North, InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(levelID, gamemode));
			InputManager::Get().AddCommand(1, Gamepad::GamepadButton::Button_East, InputManager::InputType::OnRelease, std::make_unique<SwitchSceneCommand>(3, gamemode));
		}

		//FPS object
		const auto pFPS = GetOwner()->AddCreateChild();
		pFPS->GetTransform()->SetPosition(10, 10);
		pFPS->AddComponent<FPS>(ResourceManager::Get().LoadFont("Fonts/Lingua.otf", 15), SDL_Color(255, 255, 0, 255));
	}
}
