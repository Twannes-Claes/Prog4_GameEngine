#include "Orbit.h"

#include "GameObject.h"
#include "Timer.h"
#include "Transform.h"

Monke::Orbit::Orbit(GameObject* parent)
:BaseComponent(parent)
{
}

void Monke::Orbit::Initialize()
{
	m_pTransform = GetOwner()->GetComponent<Transform>();
}

void Monke::Orbit::Update()
{
	m_Rotation += Timer::Get().GetElapsed() * m_RotSpeed;

	m_pTransform->SetLocalPosition
	(
		m_Center.x + m_Radius * cos(glm::radians(m_Rotation)),
		m_Center.y + m_Radius * sin(glm::radians(m_Rotation)) 
	);
}
