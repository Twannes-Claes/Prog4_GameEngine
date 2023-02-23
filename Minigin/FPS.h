#pragma once

#include "BaseComponent.h"

namespace Monke
{
	class FPS final : public BaseComponent
	{
	public:

		//explicit FPS_Component(std::shared_ptr<GameObject>& pParent);

		virtual ~FPS() override = default;
		FPS(const FPS& other) = delete;
		FPS(FPS&& other) = delete;
		FPS& operator=(const FPS& other) = delete;
		FPS& operator=(FPS&& other) = delete;

	private:
	};
}


