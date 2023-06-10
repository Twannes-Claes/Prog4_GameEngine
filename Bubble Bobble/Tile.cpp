#include "Tile.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Transform.h"

Monke::Tile::Tile(GameObject* parent, const bool isBigTile, const glm::ivec2 position, const int levelID)
:BaseComponent(parent)
{

	GetOwner()->GetTransform()->SetPosition(position);

	const std::string texturePath = isBigTile ? "Big.png" : "Small.png";

	m_pTexture = GetOwner()->AddComponent<Texture>(ResourceManager::Get().LoadTexture("Levels/Level" + std::to_string(levelID) + "/" + texturePath));
}
