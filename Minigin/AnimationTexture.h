#pragma once
#include "BaseComponent.h"

#include "SDL_rect.h"

namespace Monke
{
	class Transform;
	class Texture2D;

	class AnimationTexture : public Monke::BaseComponent
	{
	public:

		explicit AnimationTexture(GameObject* parent, const std::shared_ptr<Texture2D>& pTexture, int nrCols, int nrRows, int framesPerSec, bool isLeft = false);

		virtual ~AnimationTexture() override = default;

		virtual void Update() override;
		virtual void Render() const override;

		AnimationTexture(const AnimationTexture& other) = delete;
		AnimationTexture(AnimationTexture&& other) = delete;
		AnimationTexture& operator=(const AnimationTexture& other) = delete;
		AnimationTexture& operator=(AnimationTexture&& other) = delete;

	private:

		std::shared_ptr<Texture2D> m_pTexture{};

		Transform* m_pTransform;

		SDL_Rect m_SrcRect{};

		//variables for animaton
		bool m_IsLeft{};

		int m_Cols;
		int m_Rows;

		float m_FrameSec;
		float m_AccuSec;

		int m_CurFrame;

		int m_TotalFrames;
	};
}



