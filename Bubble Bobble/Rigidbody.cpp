#include "Rigidbody.h"

#include "CommandClasses.h"
#include "GameObject.h"
#include "InputManager.h"
#include "Timer.h"
#include "Transform.h"
#include "SDL_keycode.h"

Monke::Rigidbody::Rigidbody(GameObject* pParent, const glm::ivec2 boundaries, const glm::ivec2 sizePlayer)
:BaseComponent(pParent),
m_Boundaries(boundaries),
m_SizePlayer(sizePlayer)
{
	m_pTransform = GetOwner()->GetTransform();

	InputManager::Get().AddCommand(SDLK_SPACE, InputManager::InputType::OnRelease, std::make_unique<JumpCommand>(-220.f, this));
}

void Monke::Rigidbody::Update()
{

	std::cout << m_pTransform->GetWorldPosition().x << " | " << m_pTransform->GetWorldPosition().y << '\n';

	glm::vec2 pos = m_pTransform->GetWorldPosition();

	m_Velocity.y += 200.f * Timer::Get().GetElapsed();

	const glm::vec2 newPos = m_pTransform->GetLocalPosition() + (m_Velocity * Timer::Get().GetElapsed());

	m_pTransform->SetLocalPosition(newPos);

	pos = m_pTransform->GetWorldPosition();

	//boundary re-adjustment
	if(pos.x <= m_Boundaries.x)
	{
		m_pTransform->SetPosition(static_cast<float>(m_Boundaries.x), pos.y);
		pos = m_pTransform->GetWorldPosition();
	}
	if(pos.x + m_SizePlayer.x >= m_SizeLevel.x - m_Boundaries.x)
	{
		m_pTransform->SetPosition(static_cast<float>(m_SizeLevel.x - m_Boundaries.x - m_SizePlayer.x), pos.y);
		pos = m_pTransform->GetWorldPosition();
	}
	
	if (pos.y >= m_Boundaries.y)
	{
		m_pTransform->SetPosition(pos.x, static_cast<float>(m_Boundaries.y));
		pos = m_pTransform->GetWorldPosition();

		m_Velocity.y = 0.f;
	}

}
