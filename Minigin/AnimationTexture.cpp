#include "AnimationTexture.h"

#include "GameObject.h"
#include "Renderer.h"
#include "Timer.h"
#include "Texture2D.h"
#include "Transform.h"

namespace Monke
{
	//todo fix that uneven sprite sheets dont have empty animations
	//todo fix rotation
	//todo fix set function that sets new spritesheet
	AnimationTexture::AnimationTexture(GameObject* parent, const std::shared_ptr<Texture2D>& pTexture, const int nrCols, const int nrRows, const int framesPerSec, const bool isLeft)
	:BaseComponent(parent),
	 m_pTexture(pTexture)
	,m_IsLeft(isLeft)
	,m_Cols{ nrCols }
	,m_Rows{ nrRows }
	,m_FrameSec{ 1.f / framesPerSec }
	,m_AccuSec{ 0.f }
	,m_CurFrame{ 0 }
	,m_TotalFrames{ nrCols * nrRows }
	{
		m_SrcRect.w = m_pTexture->GetSize().x / m_Cols;
		m_SrcRect.h = m_pTexture->GetSize().y / m_Rows;

		m_pTransform = GetOwner()->GetTransform();
	}

	void AnimationTexture::Update()
	{
		m_AccuSec += Timer::Get().GetElapsed();
		if (m_AccuSec > m_FrameSec)
		{
			++m_CurFrame %= m_TotalFrames;
			m_AccuSec -= m_FrameSec;

			//update source rect here because render is const

			m_SrcRect.x = m_CurFrame % m_Cols * m_SrcRect.w;
			m_SrcRect.y = m_CurFrame / m_Cols * m_SrcRect.h;
		}
	}

	void AnimationTexture::Render() const
	{
		Renderer::Get().RenderTexture(*m_pTexture, m_SrcRect, m_pTransform->GetWorldPosition(), static_cast<float>(m_SrcRect.w), static_cast<float>(m_SrcRect.h));
	}
}
