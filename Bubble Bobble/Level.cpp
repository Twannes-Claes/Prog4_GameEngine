#include "Level.h"

#include <glm/vec2.hpp>

#include <fstream>

#include "GameObject.h"
#include "RapidJson/document.h"
#include "RapidJson/istreamwrapper.h"

#include "Tile.h"

Monke::Level::Level(GameObject* parent)
:BaseComponent(parent)
{
}

void Monke::Level::Initialize()
{
	//opening input file stream
	if (std::ifstream inputStream{ jsonFileName })
	{
		//making variables for json reader
		rapidjson::IStreamWrapper isw{ inputStream };
		rapidjson::Document sceneDoc;
		sceneDoc.ParseStream(isw);

		if (sceneDoc.IsArray())
		{
			for (auto it = sceneDoc.Begin(); it != sceneDoc.End(); ++it)
			{
				const rapidjson::Value& tiles{ *it };

				//check if variables are correct

				if (tiles.HasMember("name") && tiles.HasMember("positions"))
				{
					const std::string tileName{ tiles["name"].GetString() };

					bool isBigTile = tileName == "bigTile" ? true : false;

					if (const rapidjson::Value& positions{ tiles["positions"] }; positions.IsArray())
					{
						for (auto posIt = positions.Begin(); posIt != positions.End(); ++posIt)
						{
							const rapidjson::Value& currentPos{ *posIt };

							if (currentPos.IsArray() && currentPos.Size() == 2)
							{
								glm::ivec2 tilePos{};

								tilePos.x = currentPos[0].GetInt();
								tilePos.y = currentPos[1].GetInt();

								auto tileObject = new GameObject();

								tileObject->AddComponent<Tile>()->SetTile(isBigTile, tilePos);

								tileObject->SetParent(GetOwner());
							}
						}
					}
				}
			}
		}
	}
}
