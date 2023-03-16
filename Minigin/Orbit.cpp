#include "Orbit.h"

#include "GameObject.h"
#include "Time.h"
#include "Transform.h"

Monke::Orbit::Orbit(std::weak_ptr<GameObject> parent)
:UpdateComponent(parent)
{
}

void Monke::Orbit::Initialize()
{
	m_pTransform = GetOwner().lock()->GetComponent<Transform>();

	if (m_pTransform.expired())
	{
		const auto error = Expired_Weak_Ptr(__FILE__, __LINE__, "No transform component found to orbit");
	}
}

void Monke::Orbit::Update()
{
	m_Rotation += Time::GetInstance().GetElapsed() * m_RotSpeed;

	m_pTransform.lock()->SetLocalPosition(
		m_Center.x + m_Radius * cos(glm::radians(m_Rotation)),
		m_Center.y + m_Radius * sin(glm::radians(m_Rotation)) 
	);
}
