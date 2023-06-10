#include "Tile.h"

#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Transform.h"

Monke::Tile::Tile(GameObject* parent)
:BaseComponent(parent)
{
	
}

void Monke::Tile::Initialize()
{
	m_pTexture = GetOwner()->AddComponent<Texture>();

	GetOwner()->GetTransform()->SetPosition(m_Position);;

	const std::string texturePath = m_IsBigTile ? "Big.png" : "Small.png";

	m_pTexture->SetTexture(ResourceManager::Get().LoadTexture("Levels/Level1/" + texturePath));
}
