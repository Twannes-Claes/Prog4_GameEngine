#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

Monke::GameObject::~GameObject() = default;

void Monke::GameObject::Update()
{
	
}

void Monke::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void Monke::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void Monke::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}
