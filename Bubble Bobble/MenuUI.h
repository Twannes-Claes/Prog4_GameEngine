#pragma once
#include "BaseComponent.h"

namespace Monke
{
	class AnimationTexture;

	class MenuUI final : public BaseComponent
	{

	public:

		MenuUI(GameObject* pParent);

		virtual ~MenuUI() override = default;

		MenuUI(const MenuUI& other) = delete;
		MenuUI(MenuUI&& other) = delete;
		MenuUI& operator=(const MenuUI& other) = delete;
		MenuUI& operator=(MenuUI&& other) = delete;

	private:

		AnimationTexture* m_pLogo{};

		//bool m_UseSecondController{};
	};
}



